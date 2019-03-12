#include "lm_connector.h"

lmConnectorType connectorTypeFromQString(QString name)
{
	if (!name.compare("stud"))
		return LM_CONNECTOR_STUD;
	else if (!name.compare("studInlet"))
		return LM_CONNECTOR_STUD_INLET;
	else if (!name.compare("axle"))
		return LM_CONNECTOR_AXLE;
	else if (!name.compare("axleHole"))
		return LM_CONNECTOR_AXLE_HOLE;
	else if (!name.compare("cylindricalHole"))
		return LM_CONNECTOR_CYLINDRICAL_HOLE;
	else
		return LM_CONNECTOR_UNKNOWN;
}

lmConnector::lmConnector(lmConnectorType Type, lcMatrix44 Matrix)
{
	mType = Type;
	mMatrix = Matrix;
	mMultiple = false;
}

lmConnector::lmConnector(lmConnectorType Type, lcMatrix44 Matrix, qint32 Length, QString Id, QString BrotherId)
{
	mType = Type;
	mMatrix = Matrix;
	mLength = Length;
	mId = Id;
	mBrotherId = BrotherId;
	mMultiple = true;
}
