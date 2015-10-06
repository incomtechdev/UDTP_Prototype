#include <vector>
#include <map>
#include <QString>
#include <QFile>

using namespace std;

class UI_config
{
	QString configfile;
	map<QString, QString> data;

public:
	UI_config(const QString &filename);
	~UI_config();

	QString getdataValue(const QString &dataname);

};