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

#ifndef TESTVAAPI_test_va_api_fixture_h
#define TESTVAAPI_test_va_api_fixture_h

#include "test.h"
#include "test_data.h"
#include "test_defs.h"
#include "test_streamable.h"

namespace VAAPI {

// The fixture for testing class Foo.
class VAAPIFixture : public ::testing::Test {
public:
    VAAPIFixture();

    virtual ~VAAPIFixture();

    VADisplay getDisplay();
    VADisplay doInitialize();
    void doTerminate();

    void doGetMaxProfiles();
    void doGetMaxEntrypoints();
    void doGetMaxNumConfigAttribs();
    void doGetMaxValues();
    void doQueryConfigProfiles();
    const Profiles& getSupportedProfileList() const;
    bool doFindProfileInList(const VAProfile&) const;
    void doQueryConfigEntrypoints(const VAProfile&);
    const Entrypoints& getSupportedEntrypointList() const;
    bool doFindEntrypointInList(const VAEntrypoint&) const;

    void doFillConfigAttribList();
    void doGetConfigAttributes(const VAProfile&, const VAEntrypoint&);
    void doGetConfigAttributes(const VAProfile&, const VAEntrypoint&,
        ConfigAttributes& configAttrib);
    const ConfigAttributes& getConfigAttribList() const;
    const ConfigAttributes& getQueryConfigAttribList() const;
    void doCheckAttribsMatch(const ConfigAttributes&) const;
    void doCreateConfigWithAttrib(const VAProfile&, const VAEntrypoint&);
    void doQueryConfigAttributes(const VAProfile&, const VAEntrypoint&,
        const VAStatus& expectation = VA_STATUS_SUCCESS);
    void doQuerySurfacesWithConfigAttribs(const VAProfile&,
        const VAEntrypoint&);
    void doQuerySurfacesNoConfigAttribs(const VAProfile&, const VAEntrypoint&);
    void doCreateSurfaces(const VAProfile&, const VAEntrypoint&,
        const Resolution&);
    void doGetMaxSurfaceResolution(const VAProfile&, const VAEntrypoint&,
        Resolution&);
    void doGetMinSurfaceResolution(const VAProfile&, const VAEntrypoint&,
        Resolution&);
    void doCreateContext(const Resolution&,
        const VAStatus& expectation = VA_STATUS_SUCCESS);
    void doDestroyContext(const VAStatus& expectation = VA_STATUS_SUCCESS);
    void doCreateBuffer(const VABufferType&);
    void doDestroyBuffer();
    void doCreateConfigNoAttrib(const VAProfile&, const VAEntrypoint&);
    void doCreateConfig(const VAProfile&, const VAEntrypoint&);
    void doCreateConfigToFail(const VAProfile&, const VAEntrypoint&, int error);
    void doDestroyConfig();

    void doLogSkipTest(const VAProfile&, const VAEntrypoint&) const;

protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp()
    {
	// Code here will be called immediately after the constructor (right
	// before each test).
    }

    virtual void TearDown()
    {
	// Code here will be called immediately after each test (right
	// before the destructor).
    }

    // Objects declared here can be used by all tests in the test case for
    // VAAPIFixture.
    VADisplay m_vaDisplay;

private:
    char *m_restoreDriverName;
    int m_drmHandle;
    const std::string drmDevicePaths[2];

    int m_maxEntrypoints;
    int m_maxProfiles;
    int m_numProfiles;
    int m_maxConfigAttributes;

    VAConfigID m_configID;
    VAContextID m_contextID;
    VABufferID m_bufferID;

    Profiles m_profileList;
    Entrypoints m_entrypointList;
    ConfigAttributes m_configAttribList;
    ConfigAttributes m_configAttribToCreateConfig;
    ConfigAttributes m_queryConfigAttribList;
    SurfaceAttributes m_querySurfaceAttribList;
    Surfaces m_surfaceID;
};

} // namespace

#endif
