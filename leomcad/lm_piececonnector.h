#ifndef LMPIECECONNECTOR_H
#define LMPIECECONNECTOR_H

#include "lm_connector.h"

class lmPieceConnector
{
public:
	lmPieceConnector(lmConnector* Connector);

	lcMatrix44 Matrix()
	{
		return mConnector->Matrix();
	}

	bool IsMultiple()
	{
		return mConnector->IsMultiple();
	}

private:
	lmConnector* mConnector;
};

#endif // LMPIECECONNECTOR_H
