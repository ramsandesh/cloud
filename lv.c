#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>

void main()
{

   int i,val=-1,choice,choice_id,num_domains;
   int *active_domains;
   char d_name[15];
   virConnectPtr conn;
   virDomainPtr vdp;

   conn = virConnectOpen("xen:///");
   void act_dev()    //For finding Active Devices
     {
	num_domains=virConnectNumOfDomains(conn);
       	active_domains=malloc(sizeof(int) * num_domains);
       	num_domains = virConnectListDomains(conn, active_domains, num_domains);
      	printf("Active domain IDs :");
       	for (i = 0 ; i < num_domains ; i++) {
       	    printf("%d\t", active_domains[i]);
       	}
       	free(active_domains);
     }


   if (conn == NULL) {
       fprintf(stderr, "Error opening connection to XEN:///  \n");
       exit(1);
   }
   else
   {
     act_dev();
   }
  
   while(1)
   {
           
           printf("\n1.Start\n2.Suspend\n3.Resume\n4.stop\n5.exit\n ");
	   printf("please enter your choice:");
           scanf("%d",&choice);
	   if(choice==5)
		exit(1);
           switch(choice)
           {
               case 1:  
		        printf("Please enter the domain name:");
		        scanf("%s",d_name);	
		        vdp=virDomainLookupByName(conn,d_name);
      		        val=virDomainCreate(vdp);
                        if(val==0)      
                            printf("Success\n");
                        else
                          printf("Failed");  
		        break;
               case 2:
		        act_dev();
   		        printf("\n Please Insert the Active Domain ID ");
           	        scanf("%d",&choice_id);
           	        vdp=virDomainLookupByID(conn,choice_id);
      		        val=virDomainSuspend(vdp);
                        if(val==0)
                            printf("Success\n");
                        else
                            printf("Failed");  
                        break;
               case 3:
			act_dev();
		     	printf("\n Please Insert the Active Domain ID ");
           		scanf("%d",&choice_id);
           		vdp=virDomainLookupByID(conn,choice_id);
       		        val=virDomainResume(vdp);
                        if(val==0)                    
                            printf("Success\n");
                        else
                           printf("Failed");  
                        break;
               case 4: 
			act_dev();
			printf("\n Please Insert the Active Domain ID ");
           		scanf("%d",&choice_id);
         		vdp=virDomainLookupByID(conn,choice_id);
		        val=virDomainShutdown(vdp);
                        if(val==0)                    
                           printf("Success\n");
                        else
                           printf("Failed");  
                        break;
              default:exit(1);
           }//switch_ends
     }//while_ends
  virConnectClose(conn); // close connection
}

