/**
 *  @file   conf.c
 *  @author Sheng Di (sdi1@anl.gov or disheng222@gmail.com)
 *  @date   2015.
 *  @brief  Configuration loading functions for the SZ library.
 *  (C) 2015 by Mathematics and Computer Science (MCS), Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

#include "string.h"
#include "sz.h"
#include "iniparser.h"

/*-------------------------------------------------------------------------*/
/**
    @brief      It reads the configuration given in the configuration file.
    @return     integer         1 if successfull.

    This function reads the configuration given in the SZ configuration
    file and sets other required parameters.

 **/
/*-------------------------------------------------------------------------*/
int SZ_ReadConf() {
    // Check access to SZ configuration file and load dictionary
    char sol_name[256];
    char *errBoundMode;
    dictionary *ini;
    char *par;
    printf("[SZ] Reading SZ configuration file (%s) ...\n", sz_cfgFile);
    if (access(sz_cfgFile, F_OK) != 0)
    {
        printf("[SZ] Configuration file NOT accessible.\n");
        return 1;
    }
    ini = iniparser_load(sz_cfgFile);
    if (ini == NULL)
    {
        printf("[SZ] Iniparser failed to parse the conf. file.\n");
        return 1;
    }

	// Reading/setting detection parameters
	par = iniparser_getstring(ini, "ENV:SZ_CLASSPATH", NULL);
	snprintf(SZ_CLASSPATH, 256, "%s", par);
	
	par = iniparser_getstring(ini, "ENV:MAX_HEAP", NULL);
	snprintf(maxHeap, 10, "%s", par);
	
	par = iniparser_getstring(ini, "ENV:sol_name", NULL);
	snprintf(sol_name, 256, "%s", par);
	
    if(strcmp(sol_name, "SZ")==0)
		sol_ID = SZ;
	else
	{
		printf("[SZ] Error: wrong solution name (please check sz.config file)\n");
		exit(0);
	}

	if(sol_ID==SZ)
	{
		offset = (int)iniparser_getint(ini, "PARAMETER:offset", 0);
		errBoundMode = iniparser_getstring(ini, "PARAMETER:errorBoundMode", NULL);
		if(strcmp(errBoundMode,"ABS")==0||strcmp(errBoundMode,"abs")==0)
			errorBoundMode=ABS;
		else if(strcmp(errBoundMode, "REL")==0||strcmp(errBoundMode,"rel")==0)
			errorBoundMode=REL;
		else if(strcmp(errBoundMode, "ABS_AND_REL")==0||strcmp(errBoundMode, "abs_and_rel")==0)
			errorBoundMode=ABS_AND_REL;
		else if(strcmp(errBoundMode, "ABS_OR_REL")==0||strcmp(errBoundMode, "abs_or_rel")==0)
			errorBoundMode=ABS_OR_REL;
		else
		{
			printf("[SZ] Error: Wrong error bound mode (please check sz.config file)\n");
			exit(0);
		}
		
		absErrBound = (double)iniparser_getdouble(ini, "PARAMETER:absErrBound", 0);
		relBoundRatio = (double)iniparser_getdouble(ini, "PARAMETER:relBoundRatio", 0);
	}
	
    iniparser_freedict(ini);
    return 1;
}

/*-------------------------------------------------------------------------*/
/**
    @brief      It reads and tests the configuration given.
    @return     integer         1 if successfull.

    This function reads the configuration file. Then test that the
    configuration parameters are correct (including directories).

 **/
/*-------------------------------------------------------------------------*/
int SZ_LoadConf() {
    int res = SZ_ReadConf();
    if (res == 0)
    {
        printf("[SZ] ERROR: Impossible to read configuration.\n");
        return 0;
    }
    return 1;
}


