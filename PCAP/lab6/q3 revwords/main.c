#include <stdio.h>
#include <CL/cl.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SOURCE_SIZE 100000

int main()
{
	fflush(stdout);
	int i=0;
	char a[100];
	printf("\nEnter The String : ");
	gets(a);
	int n = strlen(a);
	char b[n];
	int j=0, l=0, c[100];
	while(a[i]!='\0'){
		l=0;
		while(a[i]!=32 && a[i]!='\0'){
			l++; i++;
		}
		c[j]=l;
		j++; i++;
	}
	//for(i=0; i<j; i++)
	//	printf("%d ",c[i]);

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
	//printf("Hello1");

	cl_command_queue queue = clCreateCommandQueue(context,did,NULL,&ret);

	cl_mem a_mem_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,n*sizeof(char),NULL,&ret);
	cl_mem b_mem_obj = clCreateBuffer(context,CL_MEM_WRITE_ONLY,n*sizeof(char),NULL,&ret);
	cl_mem c_mem_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,j*sizeof(int),NULL,&ret);


	ret = clEnqueueWriteBuffer(queue,a_mem_obj,CL_TRUE,0,n*sizeof(char),a,0,NULL,NULL);
	ret = clEnqueueWriteBuffer(queue,c_mem_obj,CL_TRUE,0,j*sizeof(int),c,0,NULL,NULL);
	//printf("Hello2");


	cl_program program = clCreateProgramWithSource(context,1,(const char**)&source_str,(const size_t *)&source_size,&ret);

	ret = clBuildProgram(program,1,&did,NULL,NULL,NULL);

	cl_kernel kernel = clCreateKernel(program,"revstring",&ret);

	ret = clSetKernelArg(kernel,0,sizeof(cl_mem),(void *)&a_mem_obj);
	ret = clSetKernelArg(kernel,1,sizeof(cl_mem),(void *)&c_mem_obj);
	ret = clSetKernelArg(kernel,2,sizeof(cl_mem),(void *)&b_mem_obj);


	size_t global_item_size = j;
	size_t local_item_size = 1;

	//printf("hello3");

	cl_event event;
	ret = clEnqueueNDRangeKernel(queue,kernel,1,NULL,&global_item_size,&local_item_size,0,NULL,NULL);
	ret = clFinish(queue);
	ret = clEnqueueReadBuffer(queue,b_mem_obj,CL_TRUE,0,n*sizeof(char),b,0,NULL,NULL);
	b[n]='\0';
	printf("\n%s",b);

	clFlush(queue);
	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseMemObject(a_mem_obj);
	clReleaseMemObject(b_mem_obj);
	clReleaseMemObject(c_mem_obj);
	clReleaseCommandQueue(queue);
	clReleaseContext(context);

	free(a);
	free(b);
	free(c);
	return 0;
}
