#include "include/Magazine.h"
#include "include/Subscriber.h"

Magazine::Magazine(const QString& name) :
	name(name),
	counter(0),
	condition(Condition::Init)
{
}

QString Magazine::getName() const
{
	return name;
}

void Magazine::addSubscriber(Subscriber* subscriber)
{
	subscribers.push_back(subscriber);
	++counter;
}

Magazine::Condition& Magazine::getCondition()
{
	return condition;
}

QVector<Subscriber*>& Magazine::getSubscribers()
{
	return subscribers;
}

qint32& Magazine::getCounter()
{
	return counter;
}
