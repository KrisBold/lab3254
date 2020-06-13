#include "include/Subscriber.h"


Subscriber::Subscriber(const QString& name) :
	name(name),
	isSubscribe(false),
	condition(Condition::Init)
{
}

QString Subscriber::getName() const
{
	return name;
}

QString& Subscriber::getMagazine()
{
	return magazine;
}

bool& Subscriber::subscribe()
{
	return isSubscribe;
}

Subscriber::Condition& Subscriber::getCondition()
{
	return condition;
}
