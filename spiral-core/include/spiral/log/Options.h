#ifndef SPIRAL_QPID_LOG_OPTIONS_H
#define SPIRAL_QPID_LOG_OPTIONS_H

/*
 *
 * Copyright (c) 2006 The Apache Software Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include "spiral/Options.h"
//#include "qpid/CommonImportExport.h"
#include "spiral/log/SinkOptions.h"
#include <iosfwd>
#include <memory>

namespace spiral {
namespace log {

/** Logging options for config parser. */
struct Options : public spiral::Options {
    /** Pass argv[0] for use in syslog output */
    Options(const std::string& argv0_=std::string(),
            const std::string& name_="Logging options");
    Options(const Options &);

    Options& operator=(const Options&);

    std::string argv0;
    std::string name;
    std::vector<std::string> selectors;
    bool time, level, thread, source, function;
    bool trace;
    std::string prefix;
    std::auto_ptr<SinkOptions> sinkOptions;
};

}} // namespace spiral::log

#endif  /*!SPIRAL_QPID_LOG_OPTIONS_H*/
