// **********************************************************************
//
// Copyright (c) 2003-2016 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package Ice;

public interface TwowayCallbackInt extends TwowayCallback
{
    /**
     * Called when the invocation response is received.
     *
     * @param arg The operation return value.
     **/
    void response(int arg);
}
