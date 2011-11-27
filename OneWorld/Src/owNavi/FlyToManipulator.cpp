#include <owNavi/FlyToManipulator.h>
#include <osgUtil/IntersectVisitor>

namespace owNavi
{
	FlyToManipulator::FlyToManipulator(osg::Matrix &from,osg::Matrix &to,owScene::Layer* layer,ManipulatorType type ,int tframe,float fovy)
	{
		_printOutTimingInfo = true;

		_timeOffset = 0.0;
		_timeScale = 1.0;
		_isPaused = false;

		_realStartOfTimedPeriod = 0.0;
		_animStartOfTimedPeriod = 0.0;
		_numOfFramesSinceStartOfTimedPeriod = -1;


		_ratios.clear();
		_ratiocount = 0.0;
		_layer  = layer;
		_angle = fovy;
		_tframe = tframe;
		_k = 1.0;
		_manitype = type;
		_toonear = false;
		bonce = true;
		_view = NULL;
		computeparameter(from,to);
		_needfly = generatepath();

	}

	void FlyToManipulator::home(double currentTime)
	{
		if (_animationPath.valid())
		{
			_timeOffset = _animationPath->getFirstTime()-currentTime; 

		}
		// reset the timing of the animation.
		_numOfFramesSinceStartOfTimedPeriod=-1;
	}

	void FlyToManipulator::home(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&)
	{
		home(ea.getTime());
	}

	void FlyToManipulator::init(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
	{
		home(ea,aa);
	}

	bool FlyToManipulator::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& us)
	{
		if( !valid() ) return false;

		if (bonce)
		{
			_view = dynamic_cast<osgViewer::View*>(&us);
			bonce = false;
		}

		switch( ea.getEventType() )
		{
		case osgGA::GUIEventAdapter::FRAME:
			if( _isPaused )
			{
				handleFrame( _pauseTime );
			} 
			else
			{
				handleFrame( ea.getTime() );
			}
			return false;
		case osgGA::GUIEventAdapter::PUSH:
			setoldcameramanipulator(_matrix);	
			return true;
		case osgGA::GUIEventAdapter::DRAG:
			setoldcameramanipulator(_matrix);	
			return true;
		case osgGA::GUIEventAdapter::SCROLL:
			setoldcameramanipulator(_matrix);
			return true;
		default:
			break;
		}
		return false;
	}

	void FlyToManipulator::getUsage(osg::ApplicationUsage& usage) const
	{

	}


	void FlyToManipulator::computeparameter(osg::Matrix &from,osg::Matrix &to)
	{
		osg::Matrix _inversefrom,_inverseto;
		_inversefrom.invert(from);
		_inverseto.invert(to);

		osg::Vec3d _feye,_fcenter,_fup;osg::Quat _fquat;
		from.getLookAt(_feye,_fcenter,_fup);
		_fquat =  _inversefrom.getRotate();

		osg::Vec3d _teye,_tcenter,_tup;osg::Quat _tquat;
		to.getLookAt(_teye,_tcenter,_tup);
		_tquat = _inverseto.getRotate();

		_eyes.clear();
		_eyes.push_back(_feye);
		_eyes.push_back(_teye);
		_centers.clear();
		_centers.push_back(_fcenter);
		_centers.push_back(_tcenter);
		_quats.clear();
		_quats.push_back(_fquat);
		_quats.push_back(_tquat);
		_ups.push_back(_fup);
		_ups.push_back(_tup);
		_targets.push_back(getIntersectpoint(_eyes[0],_centers[0]));
		_targets.push_back(getIntersectpoint(_eyes[1],_centers[1]));

	}

	bool FlyToManipulator::generatepath()
	{

		switch(_manitype)
		{	
			//球
		case GLOBAL:
			{
				_k = 2.0;
				if ((_eyes[0] ==_eyes[1])&&(_quats[0] == _quats[1]))//目前不判断osg::Matrix的scale参数
					return false;

				tarnsformfromgeocentric(_eyes);

				//根据视场角计算视点曲线最高点高程值
				double _distance;
				double _xrad,_yrad,_rad;
				_xrad = _eyes[0].x() - _eyes[1].x();
				if (fabs(_xrad) > 180)
					_xrad = 360.0 - fabs(_xrad);
				_yrad = _eyes[0].y() - _eyes[1].y();
				if (fabs(_yrad) > 180)
					_yrad = 360.0 - fabs(_yrad);
				_rad = osg::maximum(fabs(_xrad),fabs(_yrad));
				// _distance = osg::DegreesToRadians(_rad)*11012252*0.618;
				_distance = sin(osg::DegreesToRadians(_rad*0.5))*11012252.0*2.0;

				double mdistance = _distance/(2.0f*tanf(osg::DegreesToRadians(_angle)*0.5f));
				double	ndistance = sin(osg::DegreesToRadians(_rad*0.25))*11012252.0*2.0*sin(osg::DegreesToRadians(_rad*0.25));
				_distance = mdistance - ndistance;
				//_distance = (mdistance - ndistance)*0.618;

				double middledistance = (_eyes[0].z() + _eyes[1].z()) *0.618/**0.5*/;
				if (_distance < middledistance)
					_distance = middledistance;

				//构建视点曲线，目标点曲线，以及计算视点间时间差
				std::vector<osg::Vec3d> eyes;
				generatepoints(_eyes,_distance,eyes,_eyecurvepara);
				istoonear();
				tarnsformtogeocentric(eyes);
				tarnsformtogeocentric(_eyes);

				std::vector<osg::Vec3d> targets;
				tarnsformfromgeocentric(_targets);
				generatepoints(_targets,(_targets[0].z()+_targets[1].z())*0.5,targets,_targetcurvepara);
				tarnsformtogeocentric(targets);
				tarnsformtogeocentric(_targets);


				std::vector<double> delta_altitudes;
				for (int i = 0 ; i < (2*_tframe - 1) ; i++)
				{
					delta_altitudes.push_back(eyes[i+1].z() - eyes[i].z());
				}

				computeratios(_eyecurvepara);

				std::vector<float> _times;
				if (_ratiocount < 5.0)
					computeenoughtime(5.0,_times);
				else if (_ratiocount > 15.0)
					computeenoughtime(15.0,_times);
				else
					computetime(_times);

				std::vector<osg::Quat> quats;
				computequats(eyes,targets,quats);

				//构建飞行路径
				osg::AnimationPath * animationPath = new osg::AnimationPath;
				_animationPath = animationPath;
				_animationPath->setLoopMode(osg::AnimationPath::NO_LOOPING);

				for (int i = 0 ; i < (2*_tframe); i++)
				{
					osg::Quat quat;
					quat = quats[i];
					osg::AnimationPath::ControlPoint controlp;
					controlp.setPosition(eyes[i]);
					controlp.setRotation(quat);
					_animationPath->insert(_times[i], controlp);
				}

			}
			break;
		case PLANE:
			{
				_k = 0.5;
				if ((_eyes[0] ==_eyes[1])&&(_quats[0] == _quats[1]))//目前不判断osg::Matrix的scale参数
					return false;

				//根据视场角计算视点曲线最高点高程值
				double _distance;
				osg::Vec2d length;
				double _x = _eyes[0].x() - _eyes[1].x();
				double _y = _eyes[0].y() - _eyes[1].y();
				length.set(_x,_y);

				_distance = (length.length()/2.0)/tan(osg::DegreesToRadians(_angle));
				_distance = _distance + osg::minimum(_eyes[1].z(),_eyes[0].z());

				double middledistance = (_eyes[0].z() + _eyes[1].z()) *0.5/*/0.618*/;
				if (_distance < middledistance)
					_distance = middledistance;

				//构建视点曲线，目标点曲线，以及计算视点间时间差
				std::vector<osg::Vec3d> eyes;
				generatepoints(_eyes,_distance,eyes,_eyecurvepara);
				istoonear();

				std::vector<osg::Vec3d> targets;
				generatepoints(_targets,(_targets[0].z()+_targets[1].z())*0.5,targets,_targetcurvepara);

				computeratios(_eyecurvepara);

				std::vector<float> _times;
				if (_ratiocount < 5.0)
					computeenoughtime(5.0,_times);
				else if (_ratiocount > 15.0)
					computeenoughtime(15.0,_times);
				else
					computetime(_times);

				std::vector<osg::Quat> quats;
				computequats(eyes,targets,quats);

				//构建飞行路径
				osg::AnimationPath * animationPath = new osg::AnimationPath;
				_animationPath = animationPath;
				_animationPath->setLoopMode(osg::AnimationPath::LOOP);

				for (int i = 0 ; i < (2*_tframe) ; i++)
				{
					osg::Quat quat;
					quat = quats[i];
					osg::AnimationPath::ControlPoint controlp;
					controlp.setPosition(eyes[i]);
					controlp.setRotation(quat);
					_animationPath->insert(_times[i], controlp);
				}
			}
			break;
		default:
			return false;
		}
		return true;
	}

	void FlyToManipulator::handleFrame( double time )
	{
		osg::AnimationPath::ControlPoint cp;

		if(_numOfFramesSinceStartOfTimedPeriod==-1)
		{
			_realStartOfTimedPeriod = time;
			_timeOffset = _animationPath->getFirstTime()-time; 
		}

		double animTime = (time+_timeOffset)*_timeScale;
		//	_animationPath->getInterpolatedControlPoint( animTime, cp );
		getcontrolpoint(animTime,cp);

		if (_numOfFramesSinceStartOfTimedPeriod==-1)
		{    
			//_realStartOfTimedPeriod = time;	
			_animStartOfTimedPeriod = animTime;

		}

		++_numOfFramesSinceStartOfTimedPeriod;

		if (_printOutTimingInfo)
		{
			double delta = (animTime-_animStartOfTimedPeriod);
			if (delta>=_animationPath->getPeriod())
			{
				double frameRate = (double)_numOfFramesSinceStartOfTimedPeriod/delta;
				// reset counters for next loop.


				_realStartOfTimedPeriod = time;
				_animStartOfTimedPeriod = animTime;

				_numOfFramesSinceStartOfTimedPeriod = 0;  

				/*	setoldcameramanipulator(_matrix);*/
			}
		}

		cp.getMatrix( _matrix );
	}

	bool FlyToManipulator::generatepoints(std::vector<osg::Vec3d> &_keypoints,double _distance,std::vector<osg::Vec3d> &points,CURVEPARAMETER &curveparameter)
	{
		if (_keypoints.size() < 2)
			return false;

		osg::Vec3d midpoint = ( _keypoints[0] + _keypoints[1] ) * 0.5;
		midpoint._v[2] = _distance;
		osg::Vec3d delta_v = _keypoints[1] - _keypoints[0];

		float speed_x = delta_v._v[0]/(2*_tframe-1);
		float speed_y = delta_v._v[1]/(2*_tframe-1);

		float a = 0.0;
		float b = 0.0;
		float c = 0.0;

		c = _keypoints[0]._v[2];	//已经求出

		float c1 = (_tframe-1)*(_tframe-1);
		float c2 = _tframe-1;
		float c3 = (2*_tframe-1)*(2*_tframe-1);
		float c4 = 2*_tframe-1;
		float k1 = midpoint._v[2] - c;
		float k2 = _keypoints[1]._v[2] - c;

		float ll_1 = c3/c1;

		b = ( k2 - k1*ll_1 ) / ( c4 - c2*ll_1 );
		a = ( k2 - b*c4 ) / c3;

		osg::Vec3d point = _keypoints[0];
		for(int i=0;i<2*_tframe;i++)
		{
			point._v[0] = _keypoints[0]._v[0] +speed_x *i;
			point._v[1] = _keypoints[0]._v[1] + speed_y *i;
			point._v[2] = a*i*i + b*i + c;
			points.push_back(point);
		}

		curveparameter._a = a;
		curveparameter._b = b;
		curveparameter._c = c;
		curveparameter._sx = speed_x;
		curveparameter._cx = _keypoints[0]._v[0] ;
		curveparameter._sy = speed_y;
		curveparameter._cy = _keypoints[0]._v[1] ;

		return true;
	}

	bool  FlyToManipulator::tarnsformfromgeocentric(std::vector<osg::Vec3d> &poins)
	{
		if (!_layer)
			return false;
		if (poins.size() == 0)
			return false;

		std::vector<osg::Vec3d>::iterator iter = poins.begin();
		for (;iter != poins.end() ; iter++)
		{
			double x[1] = {(*iter).x()};
			double y[1] = {(*iter).y()};
			double z[1] = {(*iter).z()};
			double X,Y,Z;
			_layer->getDataSource()->getSP()->getSrs()->getEllipsoid()->convertXYZToLatLongHeight(x[0],y[0],z[0],X,Y,Z);//*->*/TransformFromGeoCentric(1,x,y,z);
			x[0] = X;
			y[0] = Y;
			z[0] = Z;
			(*iter).set(x[0],y[0],z[0]);
		}

		return true;
	}

	bool  FlyToManipulator::tarnsformtogeocentric(std::vector<osg::Vec3d> &poins)
	{
		if (!_layer)
			return false;
		if (poins.size() == 0)
			return false;

		std::vector<osg::Vec3d>::iterator iter = poins.begin();
		for (;iter != poins.end() ; iter++)
		{
			double x[1] = {(*iter).x()};
			double y[1] = {(*iter).y()};
			double z[1] = {(*iter).z()};
			double X,Y,Z;
			_layer->getDataSource()->getSP()->getSrs()->getEllipsoid()->convertLatLongHeightToXYZ(x[0],y[0],z[0],X,Y,Z);
			x[0] = X;
			y[0] = Y;
			z[0] = Z;
			(*iter).set(x[0],y[0],z[0]);
		}

		return true;
	}

	double FlyToManipulator::computespeed(float from,float to,CURVEPARAMETER &curveparameter)
	{
		double _a = curveparameter._a;
		double _b = curveparameter._b;
		double _c = curveparameter._c;
		double speed,speedto,speedfrom;
		speedto = _a*to*to*to/3.0+_b*to*to/2.0+_c*to;	
		speedfrom = _a*from*from*from/3.0+_b*from*from/2.0+_c*from;
		speed = /*fabs*/(speedto - speedfrom)/(to - from);

		//speed = (speedto - speedfrom)/(to - from);
		//speed = exp(speed);
		//speed = pow(1.00001,speed);
		return speed;
	}

	double FlyToManipulator::computedistance(float from,float to,CURVEPARAMETER &curveparameter)
	{
		if (from == to) 
			return 0.0;

		double _a = curveparameter._a;
		double _b = curveparameter._b;
		double _c = curveparameter._c;
		double _speedx = curveparameter._sx;
		double _speedy = curveparameter._sy;

		if (_manitype == GLOBAL)
		{
			_speedx = 1117000.0 * _speedx;
			_speedy = 1117000.0 * _speedy;
		}

		if (_toonear)
		{
			double delta_altitude = _a*to*to + _b*to  - _a*from*from - _b*from;
			double delta_x = _speedx *(to - from);
			double delta_y = _speedy* (to - from);
			osg::Vec3d length;length.set(delta_x,delta_y,delta_altitude);
			return length.length();
		}

		double a,b,c;
		a = 4*_a*_a;
		b = 4*_a*_b;
		c = _b*_b + _speedx*_speedx+_speedy*_speedy;

		double alculusfrom,alculusto,distancefrom,distanceto;
		alculusfrom = log(fabs(2*a*from+b+2*sqrtf(a)*sqrtf(a*from*from+b*from+c)))/sqrtf(a);
		alculusto = log(fabs(2*a*to+b+2*sqrtf(a)*sqrtf(a*to*to+b*to+c)))/sqrtf(a);

		distanceto = (2*a*to+b)*(sqrtf(a*to*to+b*to+c))/(4.0*a)-(b*b - 4*a*c)/(8.0*a)*(alculusto - alculusfrom);
		distancefrom = (2*a*from+b)*(sqrtf(a*from*from+b*from+c))/(4.0*a)-(b*b - 4*a*c)/(8.0*a)*(alculusto - alculusfrom);

		double distance;
		distance = distanceto - distancefrom;

		return distance;
	}

	bool FlyToManipulator::computetime(std::vector<float> &time)
	{
		float _time = 0.0;
		time.push_back(_time);
		for (int i = 0;i < (2*_tframe-1);i++)
		{
			float temp = _ratios[i]/*/_ratiocount*alltime*/;
			_time+= temp;

			if (i == (2*_tframe-2))
				_time+= temp;
			time.push_back(_time);
		}
		return true;
	}


	bool FlyToManipulator::computequats(std::vector<osg::Vec3d> &eyes,std::vector<osg::Vec3d> &targets,std::vector<osg::Quat> &quats)
	{
		//const osg::BoundingSphere &bs = _terrain->getBound();
		//std::vector<osg::Vec3d> ups;
		//ups.push_back(_ups[0]);
		//if (_manitype == GLOBAL)
		//{
		//	for (int k = 0 ; k < (2*_tframe -1) ; k++)
		//	{
		//		osg::Vec3d tempeye = eyes[k] - bs.center();
		//		osg::Vec3d temptarget = targets[k] - bs.center();
		//		osg::Vec3d axis = temptarget ^ tempeye;axis.normalize();
		//		osg::Vec3d vec =  targets[k] - eyes[k];vec.normalize();
		//		osg::Vec3d up = RotateAroudAnyVector(vec,axis,90);up.normalize();
		//		ups.push_back(up);
		//	}
		//}
		//else
		//{
		//	for (int k = 0 ; k < (2*_tframe -1) ; k++)
		//	{
		//		osg::Vec3d temp(0.0,0.0,1.0);
		//		osg::Vec3d vec =  targets[k] - eyes[k];vec.normalize();
		//		osg::Vec3d axis = vec ^ temp;axis.normalize();
		//		osg::Vec3d up = RotateAroudAnyVector(vec,axis,90);up.normalize();
		//		ups.push_back(up);
		//	}

		//}
		//ups.push_back(_ups[1]);

		//for (int i = 0 ; i < 2*_tframe ; i++)
		//{
		//	osg::Quat quat = computequat(eyes[i],targets[i],ups[i]);
		//	quats.push_back(quat);
		//}


		double fratiocount = 0.0;double sratiocount = 0.0;
		for (int w = 0; w < (2*_tframe -1);w ++)
		{
			if (w  < (_tframe -1))
			{
				fratiocount += _ratios[w];
			}
			else if (w  == (_tframe -1))
			{
				fratiocount += _ratios[w]*0.5;
				sratiocount += _ratios[w]*0.5;
			}
			else
			{
				sratiocount += _ratios[w];
			}
		}
		std::vector<osg::Vec3d> ups;
		_ups[0].normalize();
		_ups[1].normalize();
		osg::Vec3d axis = _ups[0] ^ _ups[1];axis.normalize();
		osg::Vec3d reverseaxis = axis *(-1.0);
		float angle = acosf(_ups[0] * _ups[1]);
		if (angle == 0.0)
		{
			for (int i = 0 ; i < 2*_tframe ; i++)
			{
				osg::Quat quat = computequat(eyes[i],targets[i],_ups[0]);
				quats.push_back(quat);
			}
		}
		else
		{
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			double fratio = 0.0;double sratio = 0.0;double ratio = 0.0;
			ups.push_back(_ups[0]);
			for (int q = 0; q < (2*_tframe -1);q ++)
			{
				if (q  < (_tframe -2))
				{
					ratio += _ratios[q];
					float delta_angle = angle * (ratio/_ratiocount);
					osg::Vec3d rotatevec = RotateAroudAnyVector(_ups[0],axis,delta_angle);
					rotatevec.normalize();
					ups.push_back(rotatevec);
				}
				if (q  == (_tframe -2))
				{
					ratio += _ratios[q];
					float delta_angle = angle * (ratio/_ratiocount);
					osg::Vec3d rotatevec = RotateAroudAnyVector(_ups[0],axis,delta_angle);
					rotatevec.normalize();
					ups.push_back(rotatevec);
				}
				if (q  == (_tframe -1))
				{
					ratio += _ratios[q];
					float delta_angle = angle * (1.0 - (ratio/_ratiocount));
					osg::Vec3d rotatevec = RotateAroudAnyVector(_ups[1],reverseaxis,delta_angle);
					rotatevec.normalize();
					ups.push_back(rotatevec);
				}
				if (q > (_tframe -1))
				{
					ratio += _ratios[q];
					float delta_angle = angle * (1.0 - (ratio/_ratiocount));
					osg::Vec3d rotatevec = RotateAroudAnyVector(_ups[1],reverseaxis,delta_angle);
					rotatevec.normalize();
					ups.push_back(rotatevec);
				}
			}

			for (int i = 0 ; i < 2*_tframe ; i++)
			{
				osg::Quat quat = computequat(eyes[i],targets[i],ups[i]);
				quats.push_back(quat);
			}
		}

		return true;
	}

	bool FlyToManipulator::computeenoughtime(float alltime,std::vector<float> &time)
	{
		float _time = 0.0;
		time.push_back(_time);
		for (int i = 0;i < (2*_tframe-1);i++)
		{
			float temp = _ratios[i]/_ratiocount*alltime;
			_time+= temp;

			if (i == (2*_tframe-2))
				_time+= temp;
			time.push_back(_time);
		}
		return true;
	}

	osg::Vec3d FlyToManipulator::RotateAroudAnyVector(osg::Vec3d v,osg::Vec3d n,float angle)
	{
		osg::Vec3d r;
		float vn = v*n;
		osg::Vec3d vnn = n;
		vnn*=vn;
		r = (v - vnn)* cosf(angle) + (n^v)*sinf(angle) + vnn;
		return r;
	}

	osg::Quat FlyToManipulator::computequat(osg::Vec3d &eye,osg::Vec3d &center,osg::Vec3d &up)
	{
		osg::Matrix matrix,inversematrix;
		matrix.makeLookAt(eye,center,up);
		inversematrix.invert(matrix);
		osg::Quat quat = inversematrix.getRotate();
		return quat;
	}

	bool FlyToManipulator::computeratios(CURVEPARAMETER &curveparameter)
	{
		for (int t = 0;t < (2*_tframe-1);t++)
		{
			double ratio,distance,speed;
			speed = computespeed(t,(t+1),_eyecurvepara);
			distance = computedistance(t,(t+1),_eyecurvepara);

			ratio = distance/(speed*_k);
			_ratiocount += ratio;
			_ratios.push_back(ratio);
		}
		return true;
	}

	osg::Vec3d FlyToManipulator::getIntersectpoint(osg::Vec3d spoint,osg::Vec3d epoint)
	{
		/*const osg::BoundingSphere &bs = _terrain->getBound();
		osg::Vec3d coor,temp;
		osgUtil::IntersectVisitor itsct;
		double length = (bs._center - spoint).length();
		temp = epoint - spoint;temp.normalize();
		itsct.setLODSelectionMode(osgUtil::IntersectVisitor::USE_HIGHEST_LEVEL_OF_DETAIL);
		osg::ref_ptr<osg::LineSegment> segDown = new osg::LineSegment;
		osg::Vec3d newepoint = (spoint + temp*length);
		segDown->set(spoint,newepoint);
		itsct.addLineSegment(segDown.get());
		_terrain->accept(itsct);
		if (itsct.hits())
		{
			osgUtil::IntersectVisitor::HitList& hitList = itsct.getHitList(segDown.get());
			if (!hitList.empty())
			{
				osgUtil::IntersectVisitor::HitList::iterator it = hitList.begin();
				coor = (*it).getWorldIntersectPoint();
				return coor;
			}
			else
			{
				return newepoint;
			}
		}
		else
		{
			return newepoint;
		}*/
		osg::Vec3d direct = epoint - spoint;
		double distance = 1000;
		direct.normalize();

		osg::Vec3d target;
		target = spoint + direct * distance;

		return target;
	}

	bool FlyToManipulator::getcontrolpoint(double time,osg::AnimationPath::ControlPoint& controlPoint)
	{

		if(!_animationPath.valid())
			return false;
		osg::AnimationPath::TimeControlPointMap _timeControlPointMap = _animationPath->getTimeControlPointMap();
		if (_timeControlPointMap.empty()) return false;


		osg::AnimationPath::TimeControlPointMap::const_iterator second = _timeControlPointMap.lower_bound(time);
		if (second==_timeControlPointMap.begin())
		{
			controlPoint = second->second;
		}
		else if (second!=_timeControlPointMap.end())
		{
			osg::AnimationPath::TimeControlPointMap::const_iterator first = second;
			--first;        

			double delta_time = second->first - first->first;

			if (delta_time==0.0)
				controlPoint = first->second;
			else
			{
				//如果x,y的增量均为零则曲线形为直线可直接使用osg::AnimationPath提供的插点方法，
				//若使用曲线的方法来计算则参数方程中的变量值无法计算出。

				if (_toonear)
				{
					_animationPath->getInterpolatedControlPoint( time, controlPoint );
					return false;
				}

				osg::Vec3d firstpos = first->second.getPosition();
				osg::Vec3d secondpos = second->second.getPosition();
				if (_manitype == GLOBAL)
				{
					double X,Y,Z;
					_layer->getDataSource()->getSP()->getSrs()->getEllipsoid()->convertXYZToLatLongHeight(firstpos.x(),firstpos.y(),firstpos.z(), X,Y,Z);
					firstpos.x() = X;
					firstpos.y()= Y;
					firstpos.z()= Z;
					_layer->getDataSource()->getSP()->getSrs()->getEllipsoid()->convertXYZToLatLongHeight(secondpos.x(),secondpos.y(),secondpos.z(), X,Y,Z);
					secondpos.x() = X;
					secondpos.y()= Y;
					secondpos.z()= Z;
				}

				osg::Vec3d _position,_center,_scale;osg::Quat _quat;
				_scale.set(1.0,1.0,1.0);
				float ratio = (time - first->first)/delta_time;
				_position = firstpos*(1.0-ratio) + secondpos*ratio;
				double i;
				if ((abs(_eyecurvepara._sx)) > (abs(_eyecurvepara._sy)))			 
					i = (_position.x() - (_eyecurvepara._cx))/(_eyecurvepara._sx);
				else
					i = (_position.y() - (_eyecurvepara._cy))/(_eyecurvepara._sy);


				_position.z() = _eyecurvepara._a*i*i + _eyecurvepara._b*i +_eyecurvepara._c;
				float centerx = _targetcurvepara._cx + _targetcurvepara._sx* i;
				float	 centery = _targetcurvepara._cy + _targetcurvepara._sy* i ;
				float centerz = _targetcurvepara._a*i*i+_targetcurvepara._b*i+_targetcurvepara._c;

				_center.set((_targetcurvepara._cx + i*_targetcurvepara._sx),(_targetcurvepara._cy + i * _targetcurvepara._sy),(_targetcurvepara._a*i*i+_targetcurvepara._b*i+_targetcurvepara._c));

				if (_manitype == GLOBAL)
				{
					double X,Y,Z;
					_layer->getDataSource()->getSP()->getSrs()->getEllipsoid()->convertLatLongHeightToXYZ(_position.x(),_position.y(),_position.z(),X,Y,Z);
					_position.x() = X;
					_position.y()= Y;
					_position.z()= Z;
					_layer->getDataSource()->getSP()->getSrs()->getEllipsoid()->convertLatLongHeightToXYZ(_center.x(),_center.y(),_center.z(),X,Y,Z);
					_center.x() = X;
					_center.y()= Y;
					_center.z()= Z;
				}

				osg::Quat fquat = first->second.getRotation();
				osg::Quat tquat = second->second.getRotation();
				_quat.slerp(ratio,fquat,tquat);


				controlPoint.setPosition(_position);
				controlPoint.setRotation(_quat);
				controlPoint.setScale(_scale);
			}        
		}
		else
		{
			controlPoint = _timeControlPointMap.rbegin()->second;
		}	
		return true;
	}

	void FlyToManipulator::istoonear()
	{
		double _speedx = _eyecurvepara._sx;
		double _speedy = _eyecurvepara._sy;
		if (_manitype == GLOBAL)
		{
			_speedx = 1117000.0 * _speedx;
			_speedy = 1117000.0 * _speedy;
		}
		double tempx,tempy;
		tempx = _speedx * _tframe;
		tempy = _speedy * _tframe;
		if (tempx < 10.0 && tempy < 10.0)
		{
			_toonear = true;
		}
	}

	void FlyToManipulator::setoldcameramanipulator(osg::Matrix matrix)
	{
		if (!_view)
			return;
		//if (!_terrainmanipulator.valid())
		//	return;
		//gvNavigation::TerrainManipulator* terrainManipulator = _terrainmanipulator.get();
		//_view->setCameraManipulator(_terrainmanipulator.get());	
		//terrainManipulator->setByMatrix(matrix);

		if (!_matrixmanipulator.valid())
			return;
		osgGA::CameraManipulator* matrixmanipulator = _matrixmanipulator.get();
		_view->setCameraManipulator(_matrixmanipulator.get());	
		matrixmanipulator->setByMatrix(matrix);
	}

	void FlyTo(osgViewer::View* view,owScene::Layer* layer,osg::Matrix &to)
	{
		osg::Matrix from = view->getCamera()->getViewMatrix();
		//bool bglobal = terrain->IsConvertToGeoCenteric();
		FlyToManipulator::ManipulatorType type = FlyToManipulator::GLOBAL;
		//if (!bglobal)
			//type = FlyToManipulator::PLANE;
		FlyToManipulator* flytoManipulator = new FlyToManipulator(from,to,layer,type);
		if (!flytoManipulator->bNeedFly())
			return;
		/*	gvNavigation::TerrainManipulator* terrainmanipulator = dynamic_cast<gvNavigation::TerrainManipulator*> (view->getCameraManipulator());
		if (terrainmanipulator)
		flytoManipulator->SetTerrainManipulator(terrainmanipulator);
		else
		{
		FlyToManipulator* temp = dynamic_cast<FlyToManipulator*> (view->getCameraManipulator());
		flytoManipulator->SetTerrainManipulator(temp->GetTerrainManipulator());
		}*/
		osgGA::CameraManipulator* matrixmanipulator = view->getCameraManipulator();	
		FlyToManipulator* temp = dynamic_cast<FlyToManipulator*> (view->getCameraManipulator());
		if (temp)
			flytoManipulator->SetManipulator(temp->GetManipulator());
		else
			flytoManipulator->SetManipulator(matrixmanipulator);
		view->setCameraManipulator(flytoManipulator);
	}

}