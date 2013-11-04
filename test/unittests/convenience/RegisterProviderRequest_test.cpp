/*
*
* Copyright 2013 Telefonica Investigacion y Desarrollo, S.A.U
*
* This file is part of Orion Context Broker.
*
* Orion Context Broker is free software: you can redistribute it and/or
* modify it under the terms of the GNU Affero General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* Orion Context Broker is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero
* General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with Orion Context Broker. If not, see http://www.gnu.org/licenses/.
*
* For those usages not covered by this license please contact with
* fermin at tid dot es
*
* Author: Ken Zangelin
*/
#include "gtest/gtest.h"

#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "common/globals.h"
#include "convenience/RegisterProviderRequest.h"
#include "jsonParse/jsonRequest.h"
#include "ngsi/ParseData.h"
#include "rest/ConnectionInfo.h"
#include "xmlParse/xmlRequest.h"
#include "xmlParse/xmlRegisterProviderRequest.h"

#include "testDataFromFile.h"



/* ****************************************************************************
*
* xml_ok - 
*/
TEST(RegisterProviderRequest, xml_ok)
{
  ParseData       reqData;
  const char*     fileName = "registerProviderRequest_ok.xml";
  ConnectionInfo  ci("", "POST", "1.1");

  ci.inFormat = XML;
  ci.outFormat = XML;

  EXPECT_EQ("OK", testDataFromFile(testBuf, sizeof(testBuf), fileName)) << "Error getting test data from '" << fileName << "'";

  std::string result = xmlTreat(testBuf, &ci, &reqData, RegisterProvider, "registerProviderRequest", NULL);
  EXPECT_EQ("OK", result) << "this test should be OK";

  std::string expected = "<registerProviderRequest>\n  <registrationMetadata>\n    <contextMetadata>\n      <name>ID</name>\n      <type>string</type>\n      <value>1110</value>\n    </contextMetadata>\n    <contextMetadata>\n      <name>cm2</name>\n      <type>string</type>\n      <value>XXX</value>\n    </contextMetadata>\n  </registrationMetadata>\n  <duration>PT1S</duration>\n  <providingApplication>http://kz.tid.es/abc</providingApplication>\n  <registrationId>REGISTRATION_ID</registrationId>\n</registerProviderRequest>\n";

  std::string rendered = reqData.rpr.res.render(XML, "");
  EXPECT_EQ(expected, rendered) << "bad string rendered";

  // Destroying metadata to provoke an error
  reqData.rpr.res.metadataVector.get(0)->name = "";
  std::string error;
  error = reqData.rpr.res.check(RegisterProvider, XML, "", "", 0);
  EXPECT_EQ("<discoverContextAvailabilityResponse>\n  <errorCode>\n    <code>400</code>\n    <reasonPhrase>missing metadata name</reasonPhrase>\n  </errorCode>\n</discoverContextAvailabilityResponse>\n", error);

  // sending a 'predetected error' to the check function
  error    = reqData.rpr.res.check(RegisterProvider, XML, "", "forced predetectedError", 0);
  expected = "<discoverContextAvailabilityResponse>\n  <errorCode>\n    <code>400</code>\n    <reasonPhrase>forced predetectedError</reasonPhrase>\n  </errorCode>\n</discoverContextAvailabilityResponse>\n";
  EXPECT_EQ(expected, error);

  // Just for coverage
  reqData.rpr.res.release();
  rprRelease(&reqData);
}