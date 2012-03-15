#ifndef _HTTPRESOURCESTRINGS_H_
#define _HTTPRESOURCESTRINGS_H_

#include <string>

namespace ServerBase
{
class SERVERBASE_DLL HttpResourceStrings
{
public:

	static const std::wstring hrhnFrom;
	static const std::wstring hrhnAccept;
	static const std::wstring hrhnAccept_Encoding;
	static const std::wstring hrhnAccept_Language;
	static const std::wstring hrhnUser_Agent;
	static const std::wstring hrhnReferer;
	static const std::wstring hrhnAuthorization;
	static const std::wstring hrhnCharge_To;
	static const std::wstring hrhnIf_Modified_Since;
	static const std::wstring hrhnPragma;
	static const std::wstring hrhnConnection;
	static const std::wstring hrhnAcceptCharset;

	// PREDEFINED HTTP RESPONSE HEADER NAMES
	static const std::wstring hrhnAllowed;
	static const std::wstring hrhnPublic;
	static const std::wstring hrhnContent_Length;
	static const std::wstring hrhnContent_Type;
	static const std::wstring hrhnContent_Transfer_Encoding;
	static const std::wstring hrhnContent_Encoding;
	static const std::wstring hrhnDate;
	static const std::wstring hrhnExpires;
	static const std::wstring hrhnLast_Modified;
	static const std::wstring hrhnMessage_Id;
	static const std::wstring hrhnVersion;
	static const std::wstring hrhnDerived_From;
	static const std::wstring hrhnContent_Language;
	static const std::wstring hrhnCost;
	static const std::wstring hrhnLink;
	static const std::wstring hrhnTitle;

	// PREDEFINED HTTP REQUEST METADATA
	static const std::wstring hrmServerName;
	static const std::wstring hrmServerSoftware;
	static const std::wstring hrmServerProtocol;
	static const std::wstring hrmRequestMethod;
	static const std::wstring hrmQueryString;
	static const std::wstring hrmDocumentRoot;
	static const std::wstring hrmRemoteAddr;
	static const std::wstring hrmRemoteHost;
	static const std::wstring hrmRemotePort;
	static const std::wstring hrmScriptFileName;
	static const std::wstring hrmServerAdmin;
	static const std::wstring hrmServerPort;
	static const std::wstring hrmServerSignature;
	static const std::wstring hrmPathTranslated;
	static const std::wstring hrmScriptName;
	static const std::wstring hrmRequestUri;
	static const std::wstring hrmAuthUser;
	static const std::wstring hrmAuthPwd;
	static const std::wstring hrmAuthType;

	// PREDEFINED COMMON REQUEST PARAMETERS
	static const std::wstring reqOperation;
	static const std::wstring reqVersion;
	static const std::wstring reqSession;
	static const std::wstring reqUsername;
	static const std::wstring reqPassword;
	static const std::wstring reqLocale;
	static const std::wstring reqClientAgent;
	static const std::wstring reqClientIp;
	static const std::wstring reqResponseFormat;

	// PREDEFINED RESOURCE REQUEST PARAMETERS
	static const std::wstring reqType;
	static const std::wstring reqComputeChildren;
	static const std::wstring reqDepth;
	static const std::wstring reqResourceId;
	static const std::wstring reqResourceContent;
	static const std::wstring reqResourceHeader;
	static const std::wstring reqSourceResourceId;
	static const std::wstring reqDestinationResourceId;
	static const std::wstring reqDataName;
	static const std::wstring reqDataType;
	static const std::wstring reqDataLength;
	static const std::wstring reqData;
	static const std::wstring reqOldDataName;
	static const std::wstring reqNewDataName;
	static const std::wstring reqOverwrite;
	static const std::wstring reqPackage;
	static const std::wstring reqOwner;
	static const std::wstring reqIncludeDescendants;
	static const std::wstring reqPath;
	static const std::wstring reqRecursive;
	static const std::wstring reqFilter;

	// PREDEFINED FEATURE REQUEST PARAMETERS
	static const std::wstring reqFeatProperty;
	static const std::wstring reqFeatConnectionString;
	static const std::wstring reqFeatResourceId;
	static const std::wstring reqFeatProvider;
	static const std::wstring reqFeatSchema;
	static const std::wstring reqFeatClass;
	static const std::wstring reqFeatClassNames;
	static const std::wstring reqFeatFilter;
	static const std::wstring reqFeatProperties;
	static const std::wstring reqFeatGeomProperty;
	static const std::wstring reqFeatSpatialOp;
	static const std::wstring reqFeatGeometry;
	static const std::wstring reqFeatSql;
	static const std::wstring reqFeatActiveOnly;
	static const std::wstring reqFeatComputedProperties;
	static const std::wstring reqFeatComputedAliases;

	// PREDEFINED DRAWING REQUEST PARAMETERS
	static const std::wstring reqDrawingResourceId;
	static const std::wstring reqDrawingResourceName;
	static const std::wstring reqDrawingSectionName;
	static const std::wstring reqDrawingLayerName;

	// PREDEFINED MAPPING REQUEST PARAMETERS
	static const std::wstring reqMappingMapDefinition;
	static const std::wstring reqMappingMapName;
	static const std::wstring reqMappingFeatureSetXml;
	static const std::wstring reqMappingSeqNo;
	static const std::wstring reqMappingDwfVersion;
	static const std::wstring reqMappingEmapVersion;
	static const std::wstring reqMappingEplotVersion;
	static const std::wstring reqMappingLayout;
	static const std::wstring reqMappingWidth;
	static const std::wstring reqMappingHeight;
	static const std::wstring reqMappingUnits;
	static const std::wstring reqMappingLayoutTitle;
	static const std::wstring reqMappingLayoutUnits;
	static const std::wstring reqMappingMargins;
	static const std::wstring reqMappingLayerDefinition;
	static const std::wstring reqMappingScale;
	static const std::wstring reqMappingFormat;
	static const std::wstring reqMappingType;
	static const std::wstring reqMappingThemeCategory;

	// PREDEFINED RENDERING REQUEST PARAMETERS
	static const std::wstring reqRenderingMapDefinition;
	static const std::wstring reqRenderingMapName;
	static const std::wstring reqRenderingFormat;
	static const std::wstring reqRenderingWidth;
	static const std::wstring reqRenderingHeight;
	static const std::wstring reqRenderingLayerName;
	static const std::wstring reqRenderingLayerNames;
	static const std::wstring reqRenderingMaxFeatures;
	static const std::wstring reqRenderingSelection;
	static const std::wstring reqRenderingSelectionVariant;
	static const std::wstring reqRenderingGeometry;
	static const std::wstring reqRenderingFeatureFilter;
	static const std::wstring reqRenderingBaseMapLayerGroupName;
	static const std::wstring reqRenderingTileColumn;
	static const std::wstring reqRenderingTileRow;
	static const std::wstring reqRenderingPersist;
	static const std::wstring reqRenderingScaleIndex;
	static const std::wstring reqRenderingLayerAttributeFilter;
	static const std::wstring reqRenderingKeepSelection;
	static const std::wstring reqRenderingClip;
	static const std::wstring reqRenderingBehavior;
	static const std::wstring reqRenderingSelectionColor;

	// PREDEFINED TILE REQUEST PARAMETERS
	static const std::wstring reqTileMapDefinition;

	// PREDEFINED KML REQUEST PARAMETERS
	static const std::wstring reqKmlMapDefinition;
	static const std::wstring reqKmlLayerDefinition;
	static const std::wstring reqKmlBoundingBox;
	static const std::wstring reqKmlFormat;
	static const std::wstring reqKmlWidth;
	static const std::wstring reqKmlHeight;
	static const std::wstring reqKmlDpi;
	static const std::wstring reqKmlDrawOrder;

	// PREDEFINED WEB MAP SERVICE REQUEST PARAMETERS
	static const std::wstring reqWmsRequest;
	static const std::wstring reqWmsService;
	static const std::wstring reqWmsVersion;
	static const std::wstring reqWmsLayers;
	static const std::wstring reqWmsStyles;
	static const std::wstring reqWmsCrs;
	static const std::wstring reqWmsSrs;
	static const std::wstring reqWmsBbox;
	static const std::wstring reqWmsWidth;
	static const std::wstring reqWmsHeight;
	static const std::wstring reqWmsFormat;
	static const std::wstring reqWmsQueryLayers;
	static const std::wstring reqWmsInfoFormat;
	static const std::wstring reqWmsICoord;
	static const std::wstring reqWmsJCoord;
	static const std::wstring reqWmsXCoord;
	static const std::wstring reqWmsYCoord;
	static const std::wstring reqWmsTransparent;
	static const std::wstring reqWmsBackgroundColor;
	static const std::wstring reqWmsFeatureCount;

	// PREDEFINED WEB FEATURE SERVICE REQUEST PARAMETERS
	static const std::wstring reqWfsPropertyName;
	static const std::wstring reqWfsMaxFeatures;
	static const std::wstring reqWfsSrsName;
	static const std::wstring reqWfsTypeName;
	static const std::wstring reqWfsFeatureId;
	static const std::wstring reqWfsFilter;
	static const std::wstring reqWfsBbox;

	// PREDEFINED WEB APPLICATION REQUEST PARAMETERS
	static const std::wstring reqFormat;
	static const std::wstring reqRefresh;

	// PREDEFINED OPERATIONS

	// Resource service
	static const std::wstring opEnumerateRepositories;
	static const std::wstring opCreateRepository;
	static const std::wstring opDeleteRepository;
	static const std::wstring opUpdateRepository;
	static const std::wstring opGetRepositoryContent;
	static const std::wstring opGetRepositoryHeader;
	static const std::wstring opApplyResourcePackage;

	static const std::wstring opResourceExists;
	static const std::wstring opEnumerateResources;
	static const std::wstring opSetResource;
	static const std::wstring opDeleteResource;
	static const std::wstring opMoveResource;
	static const std::wstring opCopyResource;
	static const std::wstring opGetResourceContent;
	static const std::wstring opGetResourceHeader;
	static const std::wstring opEnumerateResourceReferences;
	static const std::wstring opChangeResourceOwner;
	static const std::wstring opInheritPermissionsFrom;

	static const std::wstring opEnumerateResourceData;
	static const std::wstring opSetResourceData;
	static const std::wstring opDeleteResourceData;
	static const std::wstring opRenameResourceData;
	static const std::wstring opGetResourceData;

	static const std::wstring opEnumerateUnmanagedData;

	// Feature services
	static const std::wstring opGetFeatureProviders;
	static const std::wstring opGetConnectionPropertyValues;
	static const std::wstring opTestConnection;
	static const std::wstring opGetCapabilities;
	static const std::wstring opDescribeSchema;
	static const std::wstring opSelectFeatures;
	static const std::wstring opSelectFeaturesSpatially;
	static const std::wstring opExecuteSqlQuery;
	static const std::wstring opGetSpatialContexts;
	static const std::wstring opGetLongTransactions;
	static const std::wstring opEnumerateDataStores;
	static const std::wstring opGetSchemaMapping;
	static const std::wstring opGetSchemas;
	static const std::wstring opGetClasses;
	static const std::wstring opGetClassDefinition;
	static const std::wstring opGetIdentityProperties;
	static const std::wstring opGetFdoCacheInfo;

	// Drawing services
	static const std::wstring opGetDrawingSectionResource;
	static const std::wstring opGetDrawingSection;
	static const std::wstring opGetDrawingLayer;
	static const std::wstring opGetDrawing;
	static const std::wstring opEnumerateDrawingLayers;
	static const std::wstring opDescribeDrawing;
	static const std::wstring opEnumerateDrawingSections;
	static const std::wstring opEnumerateDrawingSectionResources;
	static const std::wstring opGetDrawingCoordinateSpace;

	// Mapping services
	static const std::wstring opGetMap;
	static const std::wstring opGetMapUpdate;
	static const std::wstring opGetPlot;
	static const std::wstring opGetLegendImage;
	static const std::wstring opGetFeatureSetEnvelope;

	// Rendering services
	static const std::wstring opGetDynamicMapOverlayImage;
	static const std::wstring opGetMapImage;
	static const std::wstring opGetMapLegendImage;
	static const std::wstring opGetVisibleMapExtent;
	static const std::wstring opQueryMapFeatures;

	// Tile services
	static const std::wstring opGetTileImage;
	static const std::wstring opClearTileCache;

	// Kml services
	static const std::wstring opGetMapKml;
	static const std::wstring opGetLayerKml;
	static const std::wstring opGetFeaturesKml;

	// WMS Operation Requests
	static const std::wstring opWmsGetCapabilities;
	static const std::wstring opWmsGetMap;
	static const std::wstring opWmsCapabilities;
	static const std::wstring opWmsMap;
	static const std::wstring opWmsGetFeatureInfo;

	// WFS Operation Requests
	static const std::wstring opWfsGetCapabilities;
	static const std::wstring opWfsGetFeature;
	static const std::wstring opWfsDescribeFeatureType;

	// Site service
	static const std::wstring opEnumerateUsers;
	static const std::wstring opEnumerateGroups;
	static const std::wstring opGetSiteVersion;
	static const std::wstring opGetSiteInfo;

	// Other requests
	static const std::wstring opCreateSession;
	static const std::wstring opGetDwfViewerPage;
	static const std::wstring opGetHtmlViewerPage;

	// Coordinate System Operation Requests
	static const std::wstring opCsConvertWktToCoordinateSystemCode;
	static const std::wstring opCsConvertCoordinateSystemCodeToWkt;
	static const std::wstring opCsConvertEpsgCodeToWkt;
	static const std::wstring opCsConvertWktToEpsgCode;
	static const std::wstring opCsEnumerateCategories;
	static const std::wstring opCsEnumerateCoordinateSystems;
	static const std::wstring opCsGetBaseLibrary;
	static const std::wstring opCsIsValid;

	// Web Applications Operations
	static const std::wstring opEnumerateApplicationTemplates;
	static const std::wstring opEnumerateApplicationWidgets;
	static const std::wstring opEnumerateApplicationContainers;


	// Coordinate System Request Parameters
	static const std::wstring reqCsWkt;
	static const std::wstring reqCsCode;
	static const std::wstring reqCsCategory;

	// PREDEFINED SITE REQUEST PARAMETERS
	static const std::wstring reqGroup;
};
}


#endif
