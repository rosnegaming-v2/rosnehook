/*
 * dump.cpp
 *
 *  Created on: May 13, 2017
 *      Author: nullifiedcat
 */

#include "common.hpp"

void PerformClassDump()
{
    ClientClass *cc = g_IBaseClient->GetAllClasses();
    FILE *cd        = fopen("/tmp/rosnehook-classdump.txt", "w");
    if (cd)
    {
        while (cc)
        {
            fprintf(cd, "[%d] %s\n", cc->m_ClassID, cc->GetName());
            cc = cc->m_pNext;
        }
        fclose(cd);
    }
}

static CatCommand do_dump("debug_dump_classes", "Dump classes", PerformClassDump);
