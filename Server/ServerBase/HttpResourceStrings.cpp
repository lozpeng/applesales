#include "stdafx.h"
#include "HttpResourceStrings.h"

namespace ServerBase {

const std::wstring HttpResourceStrings::hrhnFrom = L"From";
const std::wstring HttpResourceStrings::hrhnAccept = L"Accept";
const std::wstring HttpResourceStrings::hrhnAccept_Encoding = L"Accept-Encoding";
const std::wstring HttpResourceStrings::hrhnAccept_Language = L"Accept-Language";
const std::wstring HttpResourceStrings::hrhnUser_Agent = L"User-Agent";
const std::wstring HttpResourceStrings::hrhnReferer = L"Referer";
const std::wstring HttpResourceStrings::hrhnAuthorization = L"Authorization";
const std::wstring HttpResourceStrings::hrhnCharge_To = L"Charge-To";
const std::wstring HttpResourceStrings::hrhnIf_Modified_Since = L"If-Modified-Since";
const std::wstring HttpResourceStrings::hrhnPragma = L"Pragma";
const std::wstring HttpResourceStrings::hrhnConnection = L"Connection";
const std::wstring HttpResourceStrings::hrhnAcceptCharset = L"Accept-Charset";

const std::wstring HttpResourceStrings::hrhnAllowed = L"Allowed";
const std::wstring HttpResourceStrings::hrhnPublic = L"Public";
const std::wstring HttpResourceStrings::hrhnContent_Length = L"Content-Length";
const std::wstring HttpResourceStrings::hrhnContent_Type = L"Content-Type";
const std::wstring HttpResourceStrings::hrhnContent_Transfer_Encoding = L"Content-Transfer-Encoding";
const std::wstring HttpResourceStrings::hrhnContent_Encoding = L"Content-Encoding";
const std::wstring HttpResourceStrings::hrhnDate = L"Date";
const std::wstring HttpResourceStrings::hrhnExpires = L"Expires";
const std::wstring HttpResourceStrings::hrhnLast_Modified = L"Last-Modified";
const std::wstring HttpResourceStrings::hrhnMessage_Id = L"Message-Id";
const std::wstring HttpResourceStrings::hrhnVersion = L"Version";
const std::wstring HttpResourceStrings::hrhnDerived_From = L"Derived-From";
const std::wstring HttpResourceStrings::hrhnContent_Language = L"Content-Language";
const std::wstring HttpResourceStrings::hrhnCost = L"Cost";
const std::wstring HttpResourceStrings::hrhnLink = L"Link";
const std::wstring HttpResourceStrings::hrhnTitle = L"Title";

const std::wstring HttpResourceStrings::hrmServerName = L"ServerName";
const std::wstring HttpResourceStrings::hrmServerSoftware = L"ServerSoftware";
const std::wstring HttpResourceStrings::hrmServerProtocol = L"ServerProtocol";
const std::wstring HttpResourceStrings::hrmRequestMethod = L"RequestMethod";
const std::wstring HttpResourceStrings::hrmQueryString = L"QueryString";
const std::wstring HttpResourceStrings::hrmDocumentRoot = L"DocumentRoot";
const std::wstring HttpResourceStrings::hrmRemoteAddr = L"RemoteAddr";
const std::wstring HttpResourceStrings::hrmRemoteHost = L"RemoteHost";
const std::wstring HttpResourceStrings::hrmRemotePort = L"RemotePort";
const std::wstring HttpResourceStrings::hrmScriptFileName = L"ScriptFileName";
const std::wstring HttpResourceStrings::hrmServerAdmin = L"ServerAdmin";
const std::wstring HttpResourceStrings::hrmServerPort = L"ServerPort";
const std::wstring HttpResourceStrings::hrmServerSignature = L"ServerSignature";
const std::wstring HttpResourceStrings::hrmPathTranslated = L"PathTranslated";
const std::wstring HttpResourceStrings::hrmScriptName = L"ScriptName";
const std::wstring HttpResourceStrings::hrmRequestUri = L"RequestUri";
const std::wstring HttpResourceStrings::hrmAuthUser = L"AuthUser";
const std::wstring HttpResourceStrings::hrmAuthPwd = L"AuthPwd";
const std::wstring HttpResourceStrings::hrmAuthType = L"AuthType";

// Predefined Common Request Parameters
const std::wstring HttpResourceStrings::reqOperation = L"OPERATION";
const std::wstring HttpResourceStrings::reqVersion = L"VERSION";
const std::wstring HttpResourceStrings::reqSession = L"SESSION";
const std::wstring HttpResourceStrings::reqUsername = L"USERNAME";
const std::wstring HttpResourceStrings::reqPassword = L"PASSWORD";
const std::wstring HttpResourceStrings::reqLocale = L"LOCALE";
const std::wstring HttpResourceStrings::reqClientAgent = L"CLIENTAGENT";
const std::wstring HttpResourceStrings::reqClientIp = L"CLIENTIP";
const std::wstring HttpResourceStrings::reqResponseFormat = L"FORMAT";

// Predefined Resource Service Request Parameters
const std::wstring HttpResourceStrings::reqType = L"TYPE";
const std::wstring HttpResourceStrings::reqComputeChildren = L"COMPUTECHILDREN";
const std::wstring HttpResourceStrings::reqDepth = L"DEPTH";
const std::wstring HttpResourceStrings::reqResourceId = L"RESOURCEID";
const std::wstring HttpResourceStrings::reqResourceContent = L"CONTENT";
const std::wstring HttpResourceStrings::reqResourceHeader = L"HEADER";
const std::wstring HttpResourceStrings::reqSourceResourceId = L"SOURCE";
const std::wstring HttpResourceStrings::reqDestinationResourceId = L"DESTINATION";
const std::wstring HttpResourceStrings::reqDataName = L"DATANAME";
const std::wstring HttpResourceStrings::reqDataType = L"DATATYPE";
const std::wstring HttpResourceStrings::reqDataLength = L"DATALENGTH";
const std::wstring HttpResourceStrings::reqData = L"DATA";
const std::wstring HttpResourceStrings::reqOldDataName = L"OLDDATANAME";
const std::wstring HttpResourceStrings::reqNewDataName = L"NEWDATANAME";
const std::wstring HttpResourceStrings::reqOverwrite = L"OVERWRITE";
const std::wstring HttpResourceStrings::reqPackage = L"PACKAGE";
const std::wstring HttpResourceStrings::reqOwner = L"OWNER";
const std::wstring HttpResourceStrings::reqIncludeDescendants = L"INCLUDEDESCENDANTS";
const std::wstring HttpResourceStrings::reqPath = L"PATH";
const std::wstring HttpResourceStrings::reqRecursive = L"RECURSIVE";
const std::wstring HttpResourceStrings::reqFilter = L"FILTER";

// Resource Service Operation Requests
const std::wstring HttpResourceStrings::opEnumerateRepositories = L"ENUMERATEREPOSITORIES";
const std::wstring HttpResourceStrings::opCreateRepository = L"CREATEREPOSITORY";
const std::wstring HttpResourceStrings::opDeleteRepository = L"DELETEREPOSITORY";
const std::wstring HttpResourceStrings::opUpdateRepository = L"UPDATEREPOSITORY";
const std::wstring HttpResourceStrings::opGetRepositoryContent = L"GETREPOSITORYCONTENT";
const std::wstring HttpResourceStrings::opGetRepositoryHeader = L"GETREPOSITORYHEADER";
const std::wstring HttpResourceStrings::opApplyResourcePackage = L"APPLYRESOURCEPACKAGE";

const std::wstring HttpResourceStrings::opResourceExists = L"RESOURCEEXISTS";
const std::wstring HttpResourceStrings::opEnumerateResources = L"ENUMERATERESOURCES";
const std::wstring HttpResourceStrings::opSetResource = L"SETRESOURCE";
const std::wstring HttpResourceStrings::opDeleteResource = L"DELETERESOURCE";
const std::wstring HttpResourceStrings::opMoveResource = L"MOVERESOURCE";
const std::wstring HttpResourceStrings::opCopyResource = L"COPYRESOURCE";
const std::wstring HttpResourceStrings::opGetResourceContent = L"GETRESOURCECONTENT";
const std::wstring HttpResourceStrings::opGetResourceHeader = L"GETRESOURCEHEADER";
const std::wstring HttpResourceStrings::opEnumerateResourceReferences = L"ENUMERATERESOURCEREFERENCES";
const std::wstring HttpResourceStrings::opChangeResourceOwner = L"CHANGERESOURCEOWNER";
const std::wstring HttpResourceStrings::opInheritPermissionsFrom = L"INHERITPERMISSIONSFROM";

const std::wstring HttpResourceStrings::opEnumerateResourceData = L"ENUMERATERESOURCEDATA";
const std::wstring HttpResourceStrings::opSetResourceData = L"SETRESOURCEDATA";
const std::wstring HttpResourceStrings::opDeleteResourceData = L"DELETERESOURCEDATA";
const std::wstring HttpResourceStrings::opRenameResourceData = L"RENAMERESOURCEDATA";
const std::wstring HttpResourceStrings::opGetResourceData = L"GETRESOURCEDATA";

const std::wstring HttpResourceStrings::opEnumerateUnmanagedData = L"ENUMERATEUNMANAGEDDATA";

// Predefined Feature Service Request Parameters
const std::wstring HttpResourceStrings::reqFeatProperty = L"PROPERTY";
const std::wstring HttpResourceStrings::reqFeatConnectionString = L"CONNECTIONSTRING";
const std::wstring HttpResourceStrings::reqFeatResourceId = L"RESOURCEID";
const std::wstring HttpResourceStrings::reqFeatProvider = L"PROVIDER";
const std::wstring HttpResourceStrings::reqFeatSchema = L"SCHEMA";
const std::wstring HttpResourceStrings::reqFeatClass = L"CLASSNAME";
const std::wstring HttpResourceStrings::reqFeatClassNames = L"CLASSNAMES";
const std::wstring HttpResourceStrings::reqFeatFilter = L"FILTER";
const std::wstring HttpResourceStrings::reqFeatGeomProperty = L"GEOMPROPERTY";
const std::wstring HttpResourceStrings::reqFeatSpatialOp = L"SPATIALOP";
const std::wstring HttpResourceStrings::reqFeatGeometry = L"GEOMETRY";
const std::wstring HttpResourceStrings::reqFeatProperties = L"PROPERTIES";
const std::wstring HttpResourceStrings::reqFeatSql = L"SQL";
const std::wstring HttpResourceStrings::reqFeatActiveOnly = L"ACTIVEONLY";
const std::wstring HttpResourceStrings::reqFeatComputedProperties = L"COMPUTED_PROPERTIES";
const std::wstring HttpResourceStrings::reqFeatComputedAliases = L"COMPUTED_ALIASES";

// Feature Service Operation Requests
const std::wstring HttpResourceStrings::opGetFeatureProviders = L"GETFEATUREPROVIDERS";
const std::wstring HttpResourceStrings::opGetConnectionPropertyValues = L"GETCONNECTIONPROPERTYVALUES";
const std::wstring HttpResourceStrings::opTestConnection = L"TESTCONNECTION";
const std::wstring HttpResourceStrings::opGetCapabilities = L"GETPROVIDERCAPABILITIES";
const std::wstring HttpResourceStrings::opDescribeSchema = L"DESCRIBEFEATURESCHEMA";
const std::wstring HttpResourceStrings::opSelectFeatures = L"SELECTFEATURES";
// const std::wstring HttpResourceStrings::opSelectFeaturesSpatially = L"SELECTFEATURESSPATIALLY";
const std::wstring HttpResourceStrings::opSelectFeaturesSpatially = L"SELECTAGGREGATES";
const std::wstring HttpResourceStrings::opExecuteSqlQuery = L"EXECUTESQLQUERY";
const std::wstring HttpResourceStrings::opGetSpatialContexts = L"GETSPATIALCONTEXTS";
const std::wstring HttpResourceStrings::opGetLongTransactions = L"GETLONGTRANSACTIONS";
const std::wstring HttpResourceStrings::opEnumerateDataStores = L"ENUMERATEDATASTORES";
const std::wstring HttpResourceStrings::opGetSchemaMapping = L"GETSCHEMAMAPPING";
const std::wstring HttpResourceStrings::opGetSchemas = L"GETSCHEMAS";
const std::wstring HttpResourceStrings::opGetClasses = L"GETCLASSES";
const std::wstring HttpResourceStrings::opGetClassDefinition = L"GETCLASSDEFINITION";
const std::wstring HttpResourceStrings::opGetIdentityProperties = L"GETIDENTITYPROPERTIES";
const std::wstring HttpResourceStrings::opGetFdoCacheInfo = L"GETFDOCACHEINFO";

// Predefined Drawing Service Request Parameters
const std::wstring HttpResourceStrings::reqDrawingResourceId = L"RESOURCEID";
const std::wstring HttpResourceStrings::reqDrawingResourceName = L"RESOURCENAME";
const std::wstring HttpResourceStrings::reqDrawingSectionName = L"SECTION";
const std::wstring HttpResourceStrings::reqDrawingLayerName = L"LAYER";

// Drawing Service Operation Requests
const std::wstring HttpResourceStrings::opGetDrawingSectionResource = L"GETDRAWINGSECTIONRESOURCE";
const std::wstring HttpResourceStrings::opGetDrawingSection = L"GETDRAWINGSECTION";
const std::wstring HttpResourceStrings::opGetDrawingLayer = L"GETDRAWINGLAYER";
const std::wstring HttpResourceStrings::opGetDrawing = L"GETDRAWING";
const std::wstring HttpResourceStrings::opEnumerateDrawingLayers = L"ENUMERATEDRAWINGLAYERS";
const std::wstring HttpResourceStrings::opDescribeDrawing = L"DESCRIBEDRAWING";
const std::wstring HttpResourceStrings::opEnumerateDrawingSections = L"ENUMERATEDRAWINGSECTIONS";
const std::wstring HttpResourceStrings::opEnumerateDrawingSectionResources = L"ENUMERATEDRAWINGSECTIONRESOURCES";
const std::wstring HttpResourceStrings::opGetDrawingCoordinateSpace = L"GETDRAWINGCOORDINATESPACE";

// Mapping Service Operation Requests
const std::wstring HttpResourceStrings::opGetMap = L"GETMAP";
const std::wstring HttpResourceStrings::opGetMapUpdate = L"GETMAPUPDATE";
const std::wstring HttpResourceStrings::opGetPlot = L"GETPLOT";
const std::wstring HttpResourceStrings::opGetLegendImage = L"GETLEGENDIMAGE";
const std::wstring HttpResourceStrings::opGetFeatureSetEnvelope = L"GETFEATURESETENVELOPE";

// Predefined Mapping Service Request Parameters
const std::wstring HttpResourceStrings::reqMappingMapDefinition = L"MAPDEFINITION";
const std::wstring HttpResourceStrings::reqMappingMapName = L"MAPNAME";
const std::wstring HttpResourceStrings::reqMappingFeatureSetXml = L"FEATURESET";
const std::wstring HttpResourceStrings::reqMappingSeqNo = L"SEQNO";
const std::wstring HttpResourceStrings::reqMappingDwfVersion = L"DWFVERSION";
const std::wstring HttpResourceStrings::reqMappingEmapVersion = L"EMAPVERSION";
const std::wstring HttpResourceStrings::reqMappingEplotVersion = L"EPLOTVERSION";
const std::wstring HttpResourceStrings::reqMappingLayout = L"LAYOUT";
const std::wstring HttpResourceStrings::reqMappingWidth = L"WIDTH";
const std::wstring HttpResourceStrings::reqMappingHeight = L"HEIGHT";
const std::wstring HttpResourceStrings::reqMappingUnits = L"UNITS";
const std::wstring HttpResourceStrings::reqMappingLayoutTitle = L"LAYOUTTITLE";
const std::wstring HttpResourceStrings::reqMappingLayoutUnits = L"LAYOUTUNITTYPE";
const std::wstring HttpResourceStrings::reqMappingMargins = L"MARGINS";
const std::wstring HttpResourceStrings::reqMappingLayerDefinition = L"LAYERDEFINITION";
const std::wstring HttpResourceStrings::reqMappingScale = L"SCALE";
const std::wstring HttpResourceStrings::reqMappingFormat = L"FORMAT";
const std::wstring HttpResourceStrings::reqMappingType = L"TYPE";
const std::wstring HttpResourceStrings::reqMappingThemeCategory = L"THEMECATEGORY";

// Predefined Rendering Service Request Parameters
const std::wstring HttpResourceStrings::reqRenderingMapDefinition = L"MAPDEFINITION";
const std::wstring HttpResourceStrings::reqRenderingMapName = L"MAPNAME";
const std::wstring HttpResourceStrings::reqRenderingLayerName = L"LAYERNAME";
const std::wstring HttpResourceStrings::reqRenderingLayerNames = L"LAYERNAMES";
const std::wstring HttpResourceStrings::reqRenderingMaxFeatures = L"MAXFEATURES";
const std::wstring HttpResourceStrings::reqRenderingFormat = L"FORMAT";
const std::wstring HttpResourceStrings::reqRenderingWidth = L"WIDTH";
const std::wstring HttpResourceStrings::reqRenderingHeight = L"HEIGHT";
const std::wstring HttpResourceStrings::reqRenderingSelection = L"SELECTION";
const std::wstring HttpResourceStrings::reqRenderingSelectionVariant = L"SELECTIONVARIANT";
const std::wstring HttpResourceStrings::reqRenderingGeometry = L"GEOMETRY";
const std::wstring HttpResourceStrings::reqRenderingFeatureFilter = L"FEATUREFILTER";
const std::wstring HttpResourceStrings::reqRenderingBaseMapLayerGroupName = L"BASEMAPLAYERGROUPNAME";
const std::wstring HttpResourceStrings::reqRenderingTileColumn = L"TILECOL";
const std::wstring HttpResourceStrings::reqRenderingTileRow = L"TILEROW";
const std::wstring HttpResourceStrings::reqRenderingPersist = L"PERSIST";
const std::wstring HttpResourceStrings::reqRenderingScaleIndex = L"SCALEINDEX";
const std::wstring HttpResourceStrings::reqRenderingLayerAttributeFilter = L"LAYERATTRIBUTEFILTER";
const std::wstring HttpResourceStrings::reqRenderingKeepSelection = L"KEEPSELECTION";
const std::wstring HttpResourceStrings::reqRenderingClip = L"CLIP";
const std::wstring HttpResourceStrings::reqRenderingBehavior = L"BEHAVIOR";
const std::wstring HttpResourceStrings::reqRenderingSelectionColor = L"SELECTIONCOLOR";

// Rendering Service Operation Requests
const std::wstring HttpResourceStrings::opGetDynamicMapOverlayImage = L"GETDYNAMICMAPOVERLAYIMAGE";
const std::wstring HttpResourceStrings::opGetMapImage = L"GETMAPIMAGE";
const std::wstring HttpResourceStrings::opGetMapLegendImage = L"GETMAPLEGENDIMAGE";
const std::wstring HttpResourceStrings::opGetVisibleMapExtent = L"GETVISIBLEMAPEXTENT";
const std::wstring HttpResourceStrings::opQueryMapFeatures = L"QUERYMAPFEATURES";

// Predefined Tile Service Request Parameters
const std::wstring HttpResourceStrings::reqTileMapDefinition = L"MAPDEFINITION";

// Tile Service Operation Requests
const std::wstring HttpResourceStrings::opGetTileImage = L"GETTILEIMAGE";
const std::wstring HttpResourceStrings::opClearTileCache = L"CLEARTILECACHE";

// Predefined Kml Service Request Parameters
const std::wstring HttpResourceStrings::reqKmlMapDefinition = L"MAPDEFINITION";
const std::wstring HttpResourceStrings::reqKmlLayerDefinition = L"LAYERDEFINITION";
const std::wstring HttpResourceStrings::reqKmlBoundingBox = L"BBOX";
const std::wstring HttpResourceStrings::reqKmlFormat = L"FORMAT";
const std::wstring HttpResourceStrings::reqKmlWidth = L"WIDTH";
const std::wstring HttpResourceStrings::reqKmlHeight = L"HEIGHT";
const std::wstring HttpResourceStrings::reqKmlDpi = L"DPI";
const std::wstring HttpResourceStrings::reqKmlDrawOrder = L"DRAWORDER";

// Kml Service Operation Requests
const std::wstring HttpResourceStrings::opGetMapKml = L"GETMAPKML";
const std::wstring HttpResourceStrings::opGetLayerKml = L"GETLAYERKML";
const std::wstring HttpResourceStrings::opGetFeaturesKml = L"GETFEATURESKML";

// Predefined Web Map Service Request Parameters
const std::wstring HttpResourceStrings::reqWmsRequest = L"REQUEST";
const std::wstring HttpResourceStrings::reqWmsService = L"SERVICE";
const std::wstring HttpResourceStrings::reqWmsVersion = L"VERSION";
const std::wstring HttpResourceStrings::reqWmsLayers = L"LAYERS";
const std::wstring HttpResourceStrings::reqWmsStyles = L"STYLES";
const std::wstring HttpResourceStrings::reqWmsCrs = L"CRS";
const std::wstring HttpResourceStrings::reqWmsSrs = L"SRS";
const std::wstring HttpResourceStrings::reqWmsBbox = L"BBOX";
const std::wstring HttpResourceStrings::reqWmsWidth = L"WIDTH";
const std::wstring HttpResourceStrings::reqWmsHeight = L"HEIGHT";
const std::wstring HttpResourceStrings::reqWmsFormat = L"FORMAT";
const std::wstring HttpResourceStrings::reqWmsQueryLayers = L"QUERY_LAYERS";
const std::wstring HttpResourceStrings::reqWmsInfoFormat = L"INFO_FORMAT";
const std::wstring HttpResourceStrings::reqWmsICoord = L"I";
const std::wstring HttpResourceStrings::reqWmsJCoord = L"J";
const std::wstring HttpResourceStrings::reqWmsXCoord = L"X";
const std::wstring HttpResourceStrings::reqWmsYCoord = L"Y";
const std::wstring HttpResourceStrings::reqWmsTransparent = L"TRANSPARENT";
const std::wstring HttpResourceStrings::reqWmsBackgroundColor = L"BGCOLOR";
const std::wstring HttpResourceStrings::reqWmsFeatureCount = L"FEATURE_COUNT";

// WMS Operation Requests
const std::wstring HttpResourceStrings::opWmsGetCapabilities = L"WMS.GETCAPABILITIES";
const std::wstring HttpResourceStrings::opWmsGetMap = L"WMS.GETMAP";
const std::wstring HttpResourceStrings::opWmsCapabilities = L"WMS.CAPABILITIES";
const std::wstring HttpResourceStrings::opWmsMap = L"WMS.MAP";
const std::wstring HttpResourceStrings::opWmsGetFeatureInfo = L"WMS.GETFEATUREINFO";

// Predefined Web Feature Service Request Parameters
const std::wstring HttpResourceStrings::reqWfsPropertyName = L"PROPERTYNAME";
const std::wstring HttpResourceStrings::reqWfsMaxFeatures = L"MAXFEATURES";
const std::wstring HttpResourceStrings::reqWfsSrsName = L"SRSNAME";
const std::wstring HttpResourceStrings::reqWfsTypeName = L"TYPENAME";
const std::wstring HttpResourceStrings::reqWfsFeatureId = L"FEATUREID";
const std::wstring HttpResourceStrings::reqWfsFilter = L"FILTER";
const std::wstring HttpResourceStrings::reqWfsBbox = L"BBOX";

// Web Application Parameters
const std::wstring HttpResourceStrings::reqFormat = L"FORMAT";
const std::wstring HttpResourceStrings::reqRefresh = L"REFRESH";

// WFS Operation Requests
const std::wstring HttpResourceStrings::opWfsGetCapabilities = L"WFS.GETCAPABILITIES";
const std::wstring HttpResourceStrings::opWfsGetFeature = L"WFS.GETFEATURE";
const std::wstring HttpResourceStrings::opWfsDescribeFeatureType = L"WFS.DESCRIBEFEATURETYPE";

// Site Service Operation Requests
const std::wstring HttpResourceStrings::opEnumerateUsers = L"ENUMERATEUSERS";
const std::wstring HttpResourceStrings::opEnumerateGroups = L"ENUMERATEGROUPS";
const std::wstring HttpResourceStrings::opGetSiteVersion = L"GETSITEVERSION";
const std::wstring HttpResourceStrings::opGetSiteInfo = L"GETSITEINFO";

// Other requests
const std::wstring HttpResourceStrings::opCreateSession = L"CREATESESSION";
const std::wstring HttpResourceStrings::opGetDwfViewerPage = L"GETDWFVIEWERPAGE";
const std::wstring HttpResourceStrings::opGetHtmlViewerPage = L"GETHTMLVIEWERPAGE";

// Coordinate System Operation Requests
const std::wstring HttpResourceStrings::opCsConvertWktToCoordinateSystemCode = L"CS.CONVERTWKTTOCOORDINATESYSTEMCODE";
const std::wstring HttpResourceStrings::opCsConvertCoordinateSystemCodeToWkt = L"CS.CONVERTCOORDINATESYSTEMCODETOWKT";
const std::wstring HttpResourceStrings::opCsConvertEpsgCodeToWkt = L"CS.CONVERTEPSGCODETOWKT";
const std::wstring HttpResourceStrings::opCsConvertWktToEpsgCode = L"CS.CONVERTWKTTOEPSGCODE";
const std::wstring HttpResourceStrings::opCsEnumerateCategories = L"CS.ENUMERATECATEGORIES";
const std::wstring HttpResourceStrings::opCsEnumerateCoordinateSystems = L"CS.ENUMERATECOORDINATESYSTEMS";
const std::wstring HttpResourceStrings::opCsGetBaseLibrary = L"CS.GETBASELIBRARY";
const std::wstring HttpResourceStrings::opCsIsValid = L"CS.ISVALID";

// Web Application Operations
const std::wstring HttpResourceStrings::opEnumerateApplicationTemplates = L"ENUMERATEAPPLICATIONTEMPLATES";
const std::wstring HttpResourceStrings::opEnumerateApplicationWidgets = L"ENUMERATEAPPLICATIONWIDGETS";
const std::wstring HttpResourceStrings::opEnumerateApplicationContainers = L"ENUMERATEAPPLICATIONCONTAINERS";

// Coordinate System Request Parameters
const std::wstring HttpResourceStrings::reqCsWkt = L"CSWKT";
const std::wstring HttpResourceStrings::reqCsCode = L"CSCODE";
const std::wstring HttpResourceStrings::reqCsCategory = L"CSCATEGORY";

// Predefined Site Service Request Parameters
const std::wstring HttpResourceStrings::reqGroup = L"GROUP";

}