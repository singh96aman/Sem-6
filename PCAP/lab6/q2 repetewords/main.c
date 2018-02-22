#include <stdio.h>
#include <CL/cl.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SOURCE_SIZE 100000

int main()
{
	int i,n;
	printf("Enter value of N:");
	scanf("%d ",&n);
	char a[100];
	scanf("%s",a);
	int len = strlen(a);
	char b[len*n];
	//printf("\n %d",len);

	FILE *fp;
	char *source_str;
	size_t source_size;

	fp = fopen("kernel.cl","r");

	if(!fp)
	{
		fprintf(stderr,"Failed to load kernel\n");
		getchar();
		exit(1);
	}

	source_str = (char *)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str,1,MAX_SOURCE_SIZE,fp);

	fclose(fp);

	cl_platform_id pid = NULL;
	cl_device_id did = NULL;
	cl_uint dno;
	cl_uint pno;

	cl_int ret = clGetPlatformIDs(1,&pid,&pno);
	ret = clGetDeviceIDs(pid,CL_DEVICE_TYPE_CPU,1,&did,&dno);

	cl_context context = clCreateContext(NULL,1,&did,NULL,NULL,&ret);

	cl_command_queue queue = clCreateCommandQueue(context,did,NULL,&ret);

	cl_mem a_mem_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,len*sizeof(char),NULL,&ret);
	cl_mem b_mem_obj = clCreateBuffer(context,CL_MEM_WRITE_ONLY,len*n*sizeof(char),NULL,&ret);
	cl_mem c_mem_obj = clCreateBuffer(context,CL_MEM_WRITE_ONLY,sizeof(int),NULL,&ret);


	ret = clEnqueueWriteBuffer(queue,a_mem_obj,CL_TRUE,0,len*sizeof(char),a,0,NULL,NULL);
	ret = clEnqueueWriteBuffer(queue,c_mem_obj,CL_TRUE,0,sizeof(int),&len,0,NULL,NULL);


	cl_program program = clCreateProgramWithSource(context,1,(const char**)&source_str,(const size_t *)&source_size,&ret);

	ret = clBuildProgram(program,1,&did,NULL,NULL,NULL);

	cl_kernel kernel = clCreateKernel(program,"revstring",&ret);

	ret = clSetKernelArg(kernel,0,sizeof(cl_mem),(void *)&a_mem_obj);
	ret = clSetKernelArg(kernel,1,sizeof(cl_mem),(void *)&c_mem_obj);
	ret = clSetKernelArg(kernel,2,sizeof(cl_mem),(void *)&b_mem_obj);


	size_t global_item_size = n;
	size_t local_item_size = 1;

	cl_event event;
	ret = clEnqueueNDRangeKernel(queue,kernel,1,NULL,&global_item_size,&local_item_size,0,NULL,NULL);
	ret = clFinish(queue);
	ret = clEnqueueReadBuffer(queue,b_mem_obj,CL_TRUE,0,len*n*sizeof(char),b,0,NULL,NULL);
	b[len*n]='\0';
	printf("\n%s ",b);

	clFlush(queue);
	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseMemObject(a_mem_obj);
	clReleaseMemObject(b_mem_obj);
	clReleaseCommandQueue(queue);
	clReleaseContext(context);

	free(a);
	free(b);
	return 0;
}