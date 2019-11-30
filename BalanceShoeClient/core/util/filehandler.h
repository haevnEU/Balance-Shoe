#ifndef FILEHANDLER_H
#define FILEHANDLER_H

/* Qt system */
#include <QObject>    // Used as base class

/* Project includes */
#include "utils.h"  // Used to access project utilities

namespace haevn::esp::util{
    class FileHandler : public QObject{

        Q_OBJECT

    public static_methods:

        static FileHandler& getFileHandler(){
            static FileHandler instance; // Guaranteed to be destroyed
            return instance;
        }

    private methods:

        FileHandler();

        virtual ~FileHandler();
    };
}
#endif // FILEHANDLER_H
