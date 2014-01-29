#ifndef TRAINER_MATCHER_H
#define TRAINER_MATCHER_H

#include "dataparser.h"
#include "featureextractor2D.h"
#include "featureextractor3D.h"


class TrainerMatcher
{
	public:
		void extract_features();
		void save();
		void load();
		
};

#endif //TRAINER_MATCHER_H
