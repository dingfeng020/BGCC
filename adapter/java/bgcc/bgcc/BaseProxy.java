/***********************************************************************
  * Copyright (c) 2012, Baidu Inc. All rights reserved.
  * 
  * Licensed under the BSD License
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  * 
  *      license.txt
  *********************************************************************/

/**
 * @file     BaseProxy.java
 * @brief    
 * @author
 * @version  
 * @date     2012��08��30�� 17ʱ01��09��
 *  
 **/

package bgcc;

public class BaseProxy {

    public BaseProxy(ServerInfo serverInfo) {
        create(serverInfo);
    }

    public void finalize() {
        destroy();
    }

    public native int create(ServerInfo serverInfo);

    public native int destroy();

    public native int getErrno();

    public native int setErrno(int e);

    public native Protocol getProtocol();

    public native void putProtocol(Protocol protocol);

    public native java.lang.String getName();
    
    public native void setName(java.lang.String name);

    public native java.lang.String getWhoAmI();

    public native void setWhoAmI(java.lang.String whoami);

    public native int getTicketId(java.lang.String functionName, IntHolder ticketId,
            boolean last, Protocol inProtocol, Protocol outProtocol);

    public long proxyAddress = 0;
}

