#pragma once

#include <QObject>

class Magazine;
class Subscriber;

class FileManager final : public QObject
{
	Q_OBJECT

public:
	~FileManager();

	static FileManager& instance();

	Q_SIGNAL void addMagazine(const QString& path);
	Q_SIGNAL void addSubscriber(const QString& name);
	Q_SIGNAL void connect(const qint32& idMagazine, const qint32& idSubscriber);
	Q_SIGNAL void deleteMagazine(const qint32& index);
	Q_SIGNAL void deleteSubscriber(const qint32& index);
	Q_SIGNAL void getCounter(const qint32& index);
	Q_SIGNAL void resign(const qint32& idSubscriber, const qint32& idMagazine);
	Q_SIGNAL void clear();

	FileManager& startTerminalThread();
	FileManager& startCheckThread();

private:
	explicit FileManager();

	void Q_NORETURN terminal();
	void Q_NORETURN check();

	void printMagazines();
	void printSubscribers();

	private:
	QVector<Magazine*>		magazines;
	QVector<Subscriber*>	subscribers;
	QVector<QString>		commands;
};
