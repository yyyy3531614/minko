/*
Copyright (c) 2014 Aerys

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include "minko/Signal.hpp"

namespace minko
{
    namespace net
    {
        class HTTPRequest
        {
        public:
            HTTPRequest(const std::string& url,
                        const std::string& username = "",
                        const std::string& password = "",
                        const std::unordered_map<std::string, std::string>* additionalHeaders = nullptr);

            inline
            void
            verifyPeer(bool value)
            {
                _verifyPeer = value;
            }

            void
            run();

            std::vector<char>&
            output()
            {
                return _output;
            }

            Signal<float>::Ptr
            progress()
            {
                return _progress;
            }

            Signal<int, const std::string&>::Ptr
            error()
            {
                return _error;
            }

            Signal<const std::vector<char>&>::Ptr
            complete()
            {
                return _complete;
            }

            static
            size_t
            curlWriteHandler(void* data, size_t size, size_t chunks, void* arg);

            static
            int
            curlProgressHandler(void* arg, double total, double current, double, double);

            static
            bool
            fileExists(const std::string& filename,
                       const std::string& username = "",
                       const std::string& password = "",
                       const std::unordered_map<std::string, std::string> *additionalHeaders = nullptr,
                       bool verifyPeer = true);

        private:
            std::string _url;
            std::vector<char> _output;
            Signal<float>::Ptr _progress;
            Signal<int, const std::string&>::Ptr _error;
            Signal<const std::vector<char>&>::Ptr _complete;
            
            std::string _username;
            std::string _password;
            std::unordered_map<std::string, std::string> _additionalHeaders;
            bool _verifyPeer;
        };
    }
}
