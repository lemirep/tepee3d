
TEMPLATE = subdirs
SUBDIRS = ManageDatabaseService \
          WebServiceManagerLibrary \
          FileDownloaderLibrary


win32:win64:linux-g++-32:linux-g++-64 {
    SUBDIRS += LeapMotionControllerLibrary
}

OTHER_FILES += Documentation/how_to_service.qdoc
