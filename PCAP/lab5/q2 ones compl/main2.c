#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <cl.h>
#endif
#include <stdio.h>
#include <stdlib.h>

#define MAX_SOURCE_SIZE 100000

int main()
{
	int i,j,n;
	printf("Enter value of N:");
	scanf("%d",&n);
	int temp[n][8];

	for(i=0; i<n; i++)
		for(j=0; j<8; j++)
			scanf("%d",&temp[i][j]);

	int a[n*8], index=0;

	for(i=0;i<n;i++) 
		for(j=0; j<8; j++)
			a[index++]=temp[i][j];

	FILE *fp;
	char *source_str;
	size_t source_size;

	fp = fopen("kernel2.cl","r");

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

	cl_mem a_mem_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,8*n*sizeof(int),NULL,&ret);
	cl_mem b_mem_obj = clCreateBuffer(context,CL_MEM_WRITE_ONLY,8*n*sizeof(int),NULL,&ret);

	ret = clEnqueueWriteBuffer(queue,a_mem_obj,CL_TRUE,0,8*n*sizeof(int),a,0,NULL,NULL);

	cl_program program = clCreateProgramWithSource(context,1,(const char**)&source_str,(const size_t *)&source_size,&ret);

	ret = clBuildProgram(program,1,&did,NULL,NULL,NULL);

	cl_kernel kernel = clCreateKernel(program,"octal",&ret);

	ret = clSetKernelArg(kernel,0,sizeof(cl_mem),(void *)&a_mem_obj);
	ret = clSetKernelArg(kernel,1,sizeof(cl_mem),(void *)&b_mem_obj);

	size_t global_item_size = n;
	size_t local_item_size = 1;

	cl_event event;
	ret = clEnqueueNDRangeKernel(queue,kernel,1,NULL,&global_item_size,&local_item_size,0,NULL,NULL);

	ret = clFinish(queue);

	int b[n*8];
	ret = clEnqueueReadBuffer(queue,b_mem_obj,CL_TRUE,0,8*n*sizeof(int),b,0,NULL,NULL);

	printf("\n Answer is !\n");
	for(i=0;i<n*8;i++) 
	{
		if(i%8==0 && i!=0)
			printf("\n");
		printf("%d ",b[i]);
	}	

	clFlush(queue);
	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseMemObject(a_mem_obj);
	clReleaseMemObject(b_mem_obj);
	clReleaseCommandQueue(queue);
	clReleaseContext(context);

	//free(a);
	//free(b);
	return 0;
}