/*
 * =====================================================================================
 *
 *       Filename: variable-boolean.c
 *
 *    Description: Demo of the Optimizely SDK in C, get a feature variable boolean
 *
 *        Version: 1.0
 *        Created: 02/04/2020 15:31:46
 *       Revision: none
 *       Compiler: clang
 *
 *         Author: Ola Nordstrom (ola.nordstrom@optimizely.com)
 *   Organization: Optimizely 
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <optimizely/optimizely-sdk.h>

int main(int argc, char *argv[])
{
	char *sdkkey = getenv("OPTIMIZELY_SDKKEY"); // "YOUR SDK KEY";
	char *feature_name = getenv("OPTIMIZELY_FEATURE_NAME"); // "SOME FEATURE NAME";
	char *user_id = getenv("OPTIMIZELY_END_USER_ID"); // "OPTIMIZELY END USER ID";

	optimizely_user_attributes attrib = {0};

	attrib.id = user_id;

	if (sdkkey == NULL) {
		printf("no SDKKEY available\n");
		return -1;
	}
	int handle = optimizely_sdk_client(sdkkey);
	if (handle == -1) {
		fprintf(stderr, "failed to initialize Optimizely SDK\n");
		return 1;
	}
	char *err = NULL;
	_Bool enabled = optimizely_sdk_get_feature_variable_boolean(handle, feature_name, "boolvar", &attrib, &err);
	if (err != NULL) {
		fprintf(stderr, "failed: %s\n", err);
		free(err);
		return 1;
	}
	optimizely_sdk_delete_client(handle); // cleanup

	printf("the variable: %s is enabled: %d\n", "boolvar", enabled);

	return 0;
}
