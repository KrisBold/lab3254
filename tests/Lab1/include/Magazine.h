#pragma once

#include <QObject>

class Subscriber;

class Magazine : public QObject
{
	Q_OBJECT

public:
	explicit Magazine(const QString& name);
	~Magazine() = default;

	QString getName() const;

	void addSubscriber(Subscriber* subscriber);
	
	enum Condition
	{
		Init = 0,
		Delete,
		DeleteWin
	};

	Condition& getCondition();

	QVector<Subscriber*>& getSubscribers();
	qint32& getCounter();

private:
	QVector<Subscriber*> subscribers;
	qint32 counter;
	QString name;

	Condition condition;
};