
#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <QObject>

#include "../util/utils.h"
#include "../util/filehandler.h"

namespace haevn::esp::core{

    class UserSettings : public QObject{

        Q_OBJECT

    public static_methods:

        /**
         * @brief getFileHandler This static method returns the singleton object of the class.
         * @details This static method initializes a new instance of this class iff none exist
         *          otherwise the existing instance will be returned.
         *          This singleton implementation will provide automatic destruction if the
         *          application exits.
         * @author Nils Milewski (nimile/10010480)
         */
        static UserSettings& getUserSettings(){
            static UserSettings instance; // Guaranteed to be destroyed
            return instance;
        }

    private attributes:

        QString fileName = "user.set";
        QStringList themes;

        QString userName;
        uint userWeight;
        uint maxWeight;
        QString themeName;

    private methods:
        UserSettings();

    public methods:
        void load();
        void save();

        QString getUserName() const;
        void setUserName(const QString &value);

        uint getUserWeight() const;
        void setUserWeight(uint value);

        uint getMaxWeight() const;
        void setMaxWeight(uint value);

        QString getThemeName() const;
        void setThemeName(const QString &value);
        void setThemeName(int index);

        QString indexToThemeName(int index);
        int themeNameToIndex(QString name);
        QStringList getThemes();
    signals:
        void userNameChanged(QString name);
        void userWeightChanged(uint weight);
        void maxWeightChanged(uint weight);
        void themeChanged(QString name);
    };

}
#endif // USERSETTINGS_H
