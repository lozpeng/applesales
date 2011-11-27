#pragma once

#include <owUtil/export.h>
#include <osg/Referenced>
#include <string>
#include <iostream>

namespace owUtil
{
   /**
    * ProgressCallback is a general purpose interface for functions that need to report progress.
    */
    class OWUTIL_EXPORT ProgressBase : public osg::Referenced
    {
    public:
        /**
         * Creates a new ProgressCallback
         */
        ProgressBase();
	virtual ~ProgressBase() { }

        /**
        * Callback function that will be called.
        * @param current
        *        The current amount of work to be done.
        * @param total
        *        The total amount of work to be done.
	* @param msg
	*        Description of what is being done. Useful when total is unknown.
        * @param returns
        *        Returns true if the current task should be cancelled, false otherwise.
        */
        virtual bool reportProgress(double current, double total, const std::string& msg = std::string());

        // called when the process starts
        virtual void onStarted() { }

        // called when the process completed 
        virtual void onCompleted() { }

        void cancel() { _canceled = true; }
        bool isCanceled() const { return _canceled; }

        std::string& message() { return _message; }

        /**
         *Whether or not the task should be retried.
         */
        bool needsRetry() const { return _needsRetry;}
        /**
         *Sets whether or not the task should be retried
         */
        void setNeedsRetry( bool needsRetry ) { _needsRetry = needsRetry; }
        
    protected:
        volatile bool _canceled;
        std::string _message;
        volatile bool _needsRetry;
    };

    /**
     * ConsoleProgressCallback is a simple ProgressCallback that reports progress to the console
     */
    class OWUTIL_EXPORT ConsoleProgressCallback : public ProgressBase
    {
    public:
        /**
         * Creates a new ConsoleProgressCallback
         */
        ConsoleProgressCallback();
	virtual ~ConsoleProgressCallback() { }

        /**
        * Callback function that will be called.
        * @param current
        *        The current amount of work to be done.
        * @param total
        *        The total amount of work to be done.
        * @param returns
        *        Returns true if the current task should be cancelled, false otherwise.
        */
        virtual bool reportProgress(double current, double total, const std::string& msg = std::string());
    };
}