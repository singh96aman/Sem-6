#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <cl.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_SOURCE_SIZE 100000
#define BLOCK_SIZE 1

int main()
{
	time_t start, end;
	start = clock();

	int WA, HA;
	printf("\n Enter WA and HA : ");
	scanf("%d %d",&WA,&HA);

	int widthA = WA;
	int heightA = HA;
	int size_A = WA*HA;

	int *a = (int*) malloc(size_A*sizeof(int));
	int *rowsum = (int*) malloc(heightA*sizeof(int));
	int *colsum = (int*) malloc(widthA*sizeof(int));

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
	int i, j, k;

	printf("\n Enter the matrix : \n");
	for(i=0; i<size_A; i++)
		scanf("%d",&a[i]);

	printf("\n");

	for(i=0; i<heightA; i++){
		rowsum[i]=0;
		for(j=i*widthA; j<(i*widthA)+widthA; j++)
			rowsum[i]+=a[j];
		printf("%d ",rowsum[i]);
	}
	printf("\n");

	for(i=0; i<widthA; i++){
		colsum[i]=0;
		for(j=i, k=0; k<heightA; j=j+widthA,k++)
			colsum[i]+=a[j];
		printf("%d ",colsum[i]);
	}
	printf("\n");

	cl_platform_id pid = NULL;
	cl_device_id did = NULL;
	cl_uint dno;
	cl_uint pno;

	cl_int ret = clGetPlatformIDs(1,&pid,&pno);
	ret = clGetDeviceIDs(pid,CL_DEVICE_TYPE_CPU,1,&did,&dno);

	cl_context context = clCreateContext(NULL,1,&did,NULL,NULL,&ret);

	cl_command_queue queue = clCreateCommandQueue(context,did,NULL,&ret);

	cl_mem a_mem_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,size_A*sizeof(int),NULL,&ret);
	cl_mem rowsum_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,heightA*sizeof(int),NULL,&ret);
	cl_mem colsum_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,widthA*sizeof(int),NULL,&ret);

	ret = clEnqueueWriteBuffer(queue,a_mem_obj,CL_TRUE,0,size_A*sizeof(int),a,0,NULL,NULL);
	ret = clEnqueueWriteBuffer(queue,rowsum_obj,CL_TRUE,0,heightA*sizeof(int),rowsum,0,NULL,NULL);
	ret = clEnqueueWriteBuffer(queue,colsum_obj,CL_TRUE,0,widthA*sizeof(int),colsum,0,NULL,NULL);


	cl_program program = clCreateProgramWithSource(context,1,(const char**)&source_str,(const size_t *)&source_size,&ret);

	ret = clBuildProgram(program,1,&did,NULL,NULL,NULL);

	cl_kernel kernel = clCreateKernel(program,"mat_mul",&ret);

	ret = clSetKernelArg(kernel,0,sizeof(cl_mem),(void *)&a_mem_obj);
	ret = clSetKernelArg(kernel,1,sizeof(cl_int),(void *)&widthA);
	ret = clSetKernelArg(kernel,2,sizeof(cl_int),(void *)&heightA);
	ret = clSetKernelArg(kernel,3,sizeof(cl_mem),(void *)&rowsum_obj);
	ret = clSetKernelArg(kernel,4,sizeof(cl_mem),(void *)&colsum_obj);	

	size_t global_item_size[2] = {WA,HA};
	size_t local_item_size[2] = {BLOCK_SIZE,BLOCK_SIZE};

	cl_event event;
	ret = clEnqueueNDRangeKernel(queue,kernel,2,NULL,global_item_size,local_item_size,0,NULL,NULL);
	ret = clFinish(queue);

	cl_ulong time_start, time_end;
		double total_time;

		clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_START,sizeof(time_start),&time_start,NULL);
		clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_END,sizeof(time_end),&time_end,NULL);
		total_time = (double)(time_end-time_start);


	ret = clEnqueueReadBuffer(queue,a_mem_obj,CL_TRUE,0,size_A*sizeof(int),a,0,NULL,NULL);

	printf("\n Matrix A\n");
	for(i=0; i<size_A; i++)
	{
		printf("%d\t",a[i]);
		if(((i+1)%WA)==0)
			printf("\n");
	}

	end = clock();
		printf("\n\n Time taken to execute the KERNEL in milliseconds = %0.3f msec \n\n", total_time/1000000);
		printf("\n\n Time taken to execute the whole program in seconds : %0.3f Seconds\n",(end-start));


	clFlush(queue);
	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseMemObject(a_mem_obj);
	clReleaseCommandQueue(queue);
	clReleaseContext(context);

	free(a);
	return 0;
}