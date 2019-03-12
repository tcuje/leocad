#ifndef LM_CONNECTOR_H
#define LM_CONNECTOR_H

#include "qstring.h"
#include "lc_math.h"
#include "lm_connectortype.h"

lmConnectorType connectorTypeFromQString(QString name);

class lmConnector
{
public:
	lmConnector(lmConnectorType Type, lcMatrix44 Matrix);
	lmConnector(lmConnectorType Type, lcMatrix44 Matrix, qint32 Length, QString Id, QString BrotherId);

	QString Id()
	{
		return mId;
	}

	lcMatrix44 Matrix()
	{
		return mMatrix;
	}

	bool IsMultiple()
	{
		return mMultiple;
	}

private:
	lmConnectorType mType;
	lcMatrix44 mMatrix;
	qint32 mLength;
	QString mId;
	QString mBrotherId;

	bool mMultiple;
};

#endif // LM_CONNECTOR_H
