/*
 * Copyright (C) 2016 Intel Corporation. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "test_va_api_fixture.h"

namespace VAAPI {

class VAAPIGetCreateConfig
    : public VAAPIFixture
    , public ::testing::WithParamInterface<std::tuple<VAProfile, VAEntrypoint> >
{
public:
    VAAPIGetCreateConfig()
    {
        m_vaDisplay = doInitialize();
    }

    virtual ~VAAPIGetCreateConfig()
    {
        doTerminate();
    }
};

TEST_P(VAAPIGetCreateConfig, CreateConfigWithAttributes)
{
    const VAProfile& profile        = ::testing::get<0>(GetParam());
    const VAEntrypoint& entrypoint  = ::testing::get<1>(GetParam());

    doGetMaxValues();
    doQueryConfigProfiles();

    if (doFindProfileInList(profile)) {
        doQueryConfigEntrypoints(profile);
        if (doFindEntrypointInList(entrypoint)) {
            // profile and entrypoint are supported
            doFillConfigAttribList();
            doGetConfigAttributes(profile, entrypoint);
            doCreateConfigWithAttrib(profile, entrypoint);
            doDestroyConfig();
        } else {
            // entrypoint is not supported by driver
            doCreateConfigToFail(profile, entrypoint,
                VA_STATUS_ERROR_UNSUPPORTED_ENTRYPOINT);
        }
    } else {
        // profile is not supported by this driver
        doCreateConfigToFail(profile, entrypoint,
            VA_STATUS_ERROR_UNSUPPORTED_PROFILE);
    }
}

TEST_P(VAAPIGetCreateConfig, CreateConfigNoAttributes)
{
    const VAProfile& profile        = ::testing::get<0>(GetParam());
    const VAEntrypoint& entrypoint  = ::testing::get<1>(GetParam());

    doGetMaxValues();
    doQueryConfigProfiles();

    if (doFindProfileInList(profile)) {
        doQueryConfigEntrypoints(profile);
        if (doFindEntrypointInList(entrypoint)) {
            // profile and entrypoint are supported
            doCreateConfigNoAttrib(profile, entrypoint);
            doDestroyConfig();
        } else {
            // entrypoint is not supported by driver
            doCreateConfigToFail(profile, entrypoint,
                VA_STATUS_ERROR_UNSUPPORTED_ENTRYPOINT);
        }
    } else {
        // profile is not supported by this driver
        doCreateConfigToFail(profile, entrypoint,
            VA_STATUS_ERROR_UNSUPPORTED_PROFILE);
    }
}

INSTANTIATE_TEST_CASE_P(
    GetCreateConfig, VAAPIGetCreateConfig,
    ::testing::Combine(::testing::ValuesIn(m_vaProfiles),
                       ::testing::ValuesIn(m_vaEntrypoints)));

} // namespace VAAPI
