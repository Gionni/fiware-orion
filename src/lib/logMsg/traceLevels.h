#ifndef TRACE_LEVELS_H
#define TRACE_LEVELS_H

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



/* ****************************************************************************
*
* TraceLevels - 
*/
typedef enum TraceLevels
{
  /* The "tracelevels" group are largely based on the different processing levels used
   * at Context Broker */

  /* Rest (20-39) */
  LmtRest = 20,
  LmtRest2,        // More depth of messages for LmtRest,
  LmtRestCompare,
  LmtUrlParse,
  LmtHttpRequest,
  LmtHttpHeaders,
  LmtHttpDaemon,
  LmtHttpPayload,
  LmtMhd,
  LmtRestReply,
  LmtSavedResponse,

  /* Parser (40-59) */
  LmtParse    = 40,
  LmtPresent,
  LmtNew,
  LmtTreat,
  LmtDump,
  LmtNullNode,

  /* RestService and Service (60-79) */
  LmtConvenience = 60,
  LmtService,

  /* ConvenienceMap (80-99) */
  LmtClone = 80,

  /* MongoBackend (100-119) */
  LmtMongo = 100,

  /* Cleanup (120-139) */
  LmtDestructor = 120,
  LmtRelease,
  LmtMetadataDoubleFree,

  /* Types (140-159) */
  LmtEntityId = 140,
  LmtRestriction,
  LmtScope,

  /* Notifications (160-179) */
  LmtNotifier = 160,

  /* Others (>=180) */
  LmtCm = 180,
  LmtIotaXmlReg,
  LmtIotaXmlObs,

  LmtHeavyTest = 255

} TraceLevels;



/* ****************************************************************************
*
* traceLevelName - 
*/
extern char* traceLevelName(TraceLevels level);

#endif