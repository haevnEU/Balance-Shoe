/**
 * @file filehandler.h
 * @brief Provides interaction with the filesystem
 * @details This file contains the interaction with the filesystem.
 * @note This is not yet implemented
 * @author Nils Milewski (nimile/10010480)
 */

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

        /**
         * @brief getFileHandler This static method returns the singleton object of the class.
         * @details This static method initializes a new instance of this class iff none exist
         *          otherwise the existing instance will be returned.
         *          This singleton implementation will provide automatic destruction if the
         *          application exits.
         * @author Nils Milewski (nimile/10010480)
         */
        static FileHandler& getFileHandler(){
            static FileHandler instance; // Guaranteed to be destroyed
            return instance;
        }

    private methods:

        /**
         * @brief FileHandler This constructor initializes a new instance of this class.
         * @author Nils Milewski (nimile/10010480)
         */
        FileHandler();

        /**
         * @brief ~FileHandler Destructor
         * @author Nils Milewski (nimile/10010480)
         */
        virtual ~FileHandler();

    public methods:
        void save(QString data, QString path);

        QString read(QString path);
    };
}
#endif // FILEHANDLER_H
