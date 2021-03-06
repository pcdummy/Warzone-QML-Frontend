// Copyright (c) 2010, Razvan Petru
// Copyright (C) 2011, Jochum Rene
// All rights reserved.

// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:

// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice, this
//   list of conditions and the following disclaimer in the documentation and/or other
//   materials provided with the distribution.
// * The name of the contributors may not be used to endorse or promote products
//   derived from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef __LIB_WZLOG_LOGGERDEST_H__
#define __LIB_WZLOG_LOGGERDEST_H__

#include <QString>
#include <QFile>
#include <QTextStream>

namespace WzLog {

class LoggerDestination
{
public:
    virtual ~LoggerDestination(){}
    virtual void write(const QString& message) = 0;
    void setAlwaysFlush(bool state = false)
    {
        alwaysFlush = state;
    }
protected:
    bool alwaysFlush;
};

class LoggerFileDestination : public LoggerDestination
{
public:
   LoggerFileDestination(const QString& filePath);
   void write(const QString& message);

private:
   QFile mFile;
   QTextStream mOutputStream;
};

class LoggerDebugOutputDestination : public LoggerDestination
{
public:
   void write(const QString& message);
};

class LoggerWinDebugDestition: public LoggerDestination
{
public:
   void write(const QString& message);
};

} // namespace WzLog {

#endif // __LIB_WZLOG_LOGGERDEST_H__
