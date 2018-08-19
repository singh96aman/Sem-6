#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <cl.h>
#endif
#include <stdio.h>
#include <stdlib.h>

#define MAX_SOURCE_SIZE 1000000

int main()
{
	int i, n=5;
	int a[5]={1,2,3,4,5};
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

	cl_platform_id pid;
	cl_device_id did;
	cl_uint pno, dno;

	cl_int ret = clGetPlatformIDs(1, &pid, &pno);
	ret = clGetDeviceIDs(pid,CL_DEVICE_TYPE_CPU,1, &did, &dno);
	cl_context context = clCreateContext(NULL,1,&did,NULL,NULL,&ret);
	cl_command_queue queue = clCreateCommandQueue(context, did,NULL,&ret);

	cl_mem a_mem_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,sizeof(int)*n,NULL,&ret);
	cl_mem b_mem_obj = clCreateBuffer(context,CL_MEM_WRITE_ONLY,sizeof(int)*n,NULL,&ret);

	ret = clEnqueueWriteBuffer(queue,a_mem_obj,CL_TRUE,0,sizeof(int)*n,a,0,NULL,NULL);

	cl_program program = clCreateProgramWithSource(context,1,(const char**)&source_str, (const size_t*)&source_size, &ret);
	ret = clBuildProgram(program,1,&did,NULL,NULL,NULL);

	cl_kernel kernel =clCreateKernel(program,"add",&ret);

	ret = clSetKernelArg(kernel,0,sizeof(cl_mem),(void*)&a_mem_obj);
	ret = clSetKernelArg(kernel,1,sizeof(cl_mem),(void*)&b_mem_obj);

	size_t global_item_size=n;
	size_t local_item_size=1;

	ret = clEnqueueNDRangeKernel(queue,kernel,1,NULL,&global_item_size,&local_item_size,0,NULL,NULL);

	ret = clFinish(queue);

	int b[n];
	ret = clEnqueueReadBuffer(queue,b_mem_obj,CL_TRUE,0,sizeof(int)*n,b,0,NULL,NULL);

	for(i=0; i<n; i++)
		printf("\n%d",b[i]);

	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseMemObject(a_mem_obj);
	clReleaseMemObject(b_mem_obj);
	clReleaseCommandQueue(queue);
	clReleaseContext(context);

	return 0;

}