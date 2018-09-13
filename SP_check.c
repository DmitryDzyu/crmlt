int getcounter() {
	return atoi(lr_eval_string("{fieldscouner}"));
}

void inccounter() {
	int a;
	char st[100];
	a=getcounter()+1;
	sprintf(st,"%d",a);
	lr_save_string(st,"fieldscouner");
}

void getdateforlogin() {
	
	lr_save_string("0","fieldscouner");
	
	lr_save_string("","Applet");
	
	lr_save_string("","View");
	
	web_reg_save_param("Header", "LB=^v^", "RB=^","Ord=1","Search=Body", "Notfound=warning", LAST);
	
	web_reg_save_param("View", "LB=^View^", "RB=^","Ord=1","Notfound=warning", LAST);
	
	web_reg_save_param("Applet", "LB=&SWEApplet=", "RB=^","Ord=1", "Notfound=warning", LAST);
	
}


void getdate() {
	
	
	lr_save_string("","Applet");
	
	lr_save_string("","View");
	
	web_reg_save_param("Header", "LB=`v`", "RB=`","Ord=1","Search=Body", "Notfound=warning", LAST);
	
	web_reg_save_param("TypeApplets", "LB=`Status`", "RB=`","Ord=1","Search=Body", "Notfound=warning", LAST);
	
	web_reg_save_param_regexp ("ParamName=flagforheader",
		"RegExp=`v`.*?`(.*?)`.*?`",
		"Ordinal=1",
		"Notfound=warning",
	LAST);
	
	/*web_reg_save_param_regexp ("ParamName=applets",
		"RegExp=`cud`(.(?!([c][u][d])))*?`ObjectName`(([^`](?!([c][u][d])))*?)`(.(?!([c][u][d])))*?`sp`(.(?!([c][u][d])))*?`",
		"Group=3",
		"Ordinal=all",
		"Notfound=warning",
	LAST);*/
	
	web_reg_save_param_regexp ("ParamName=applets1",
		"RegExp=(`cud`.*?`ObjectName`.*?`.*?`sp`.*?`)",
		"Ordinal=all",
		"Notfound=warning",
	LAST);
	
	web_reg_save_param_regexp ("ParamName=views",
		"RegExp=`cud`.*?`ObjectName`.*?`.*?`sp`.*?`.*?`SWEView`(.*?)`",
		"Ordinal=all",
		"Notfound=warning",
	LAST);
	
	/*web_reg_save_param_regexp ("ParamName=fieldsnames",
		"RegExp=`cud`(.(?!([c][u][d])))*?`ObjectName`(.(?!([c][u][d])))*?`sp`(([^`](?!([c][u][d])))*?)`",
		"Group=5",
		"Ordinal=all",
		"Notfound=warning",
	LAST);*/
	
	web_reg_save_param_regexp ("ParamName=fieldsnames",
		"RegExp=`cud`.*?`ObjectName`.*?`.*?`sp`(.*?)`",
		"Ordinal=all",
		"Notfound=warning",
	LAST);	
	
	web_reg_save_param_regexp (
		"ParamName=strings",
		"RegExp=`sp`(.*?`dn`.*?`fn`.*?`)",
	    "Ordinal=All",
	    "Notfound=warning",
    LAST );
	
	web_reg_save_param_regexp (
		"ParamName=fn",
		"RegExp=`sp`.*?`dn`.*?`fn`(.*?)`",
	    "Ordinal=All",
	    "Notfound=warning",
    LAST );
	
	web_reg_save_param_regexp (
		"ParamName=dn",
		"RegExp=`sp`.*?`dn`(.*?)`fn`.*?`",
	    "Ordinal=All",
	    "Notfound=warning",
    LAST );
	
	web_reg_save_param_regexp (
		"ParamName=fields",
		"RegExp=`sp`(.*?)`.*?`dn`.*?`fn`.*?`",
	    "Ordinal=All",
	    "Notfound=warning",
    LAST );
	
	web_reg_save_param_regexp ("ParamName=fieldmethod",
		"RegExp=`SWEField`.*?`.*?`SWEMethod`(.*?)`",
		"Ordinal=all",
		"Notfound=warning",
	LAST);
	
	web_reg_save_param_regexp ("ParamName=fieldnamemethod",
		"RegExp=`SWEField`(.*?)`.*?`SWEMethod`.*?`",
		"Ordinal=all",
		"Notfound=warning",
	LAST);
	
	web_reg_save_param("View", "LB=`View`", "RB=`","Ord=1","Notfound=warning", LAST);
	
	web_reg_save_param("Applet", "LB=&SWEApplet=", "RB=`","Ord=1", "Notfound=warning", LAST);
	
}

void getelemfromstring(char *temp, char *name) {
	char st[500],st1[500];
	int n,i,f=0,k=0,z,kol=0,kl=1,j;
	n=strlen(temp);
	for (i=0;i<n;i++) {
		if (temp[i]>='0' && temp[i]<='9') {
			kol=kol*10+temp[i]-48;
		}
		if (temp[i]=='*') {
			for (j=0;j<kol;j++) {
				st[j]=temp[i+1+j];
			}
			st[kol]='\0';
			sprintf(st1,"%s_%d",name,getcounter());
			inccounter();
			i=i+kol;
			kol=0;
			kl++;
			lr_save_string(st,st1);
		}
	}
}

void createparamforfields() {
	int i,k,kl1,num,kl,a,f,*m,kl2=1,j,kl3,z=1,y=1,flag=0,ii;
	int *m1;
	char st[500],*temp,s[1000],s2[300],s1[1000],st1[500],*temp1,*c,*b,status[10]="NewPopup";
	//long file;
	//file=fopen ("output.txt","a");
	temp=lr_paramarr_idx("views",1);
	lr_save_string(lr_eval_string("{applets1_count}"),"applets_count");
	for (i=1;i<=lr_paramarr_len("applets1");i++) {
		sprintf(st,"applets_%d",i);
		lr_save_param_regexp(lr_paramarr_idx("applets1",i), strlen(lr_paramarr_idx("applets1",i)), "RegExp=`ObjectName`(.*?)`", "Ordinal=All", "ResultParam=applets2", LAST);
		lr_save_string(lr_paramarr_idx("applets2",lr_paramarr_len("applets2")),st);
	}
	for (i=1;i<=lr_paramarr_len("applets");i++) {
		temp1=lr_paramarr_idx("applets",i);
		sprintf(s,"{%s_%s}",temp,temp1);
		if (lr_eval_string(s)[0]!='1' || strcmp(lr_eval_string("{TypeApplets}"),status)==0) {
			flag=1;
			//sprintf(s,"%s_%s",temp,temp1);
			//lr_save_string("1",s);
		}
	}
	temp1=lr_paramarr_idx("applets",kl2);
	sprintf(s2,"{%s_%s}",temp,temp1);
if (lr_eval_string("{Header}")[0] && (lr_eval_string("{flagforheader}")[0]=='0' || lr_eval_string("{flagforheader}")[0]=='2' || lr_eval_string("{flagforheader}")[0]=='1') || getcounter()==0) {
		lr_save_string(lr_eval_string("{Header}"),temp);
		getelemfromstring(lr_eval_string("{Header}"),"namefield");
	}
	if (flag==1) {
	//	m1=(int *)calloc(lr_paramarr_len("fieldmethod"),lr_paramarr_len,sizeof(int));
		m=(int *)calloc(getcounter(),sizeof(int));
		//lr_output_message("%d",getcounter());
		for (i=1;i<=lr_paramarr_len("fields");i++) {
			for (ii=1;ii<=lr_paramarr_len("fieldsnames");ii++) {
				if (strcmp(lr_paramarr_idx("fieldsnames",ii),lr_paramarr_idx("fields",i))==0) {
					//lr_output_message("%s %s",lr_paramarr_idx("fieldsnames",kl2+1),lr_paramarr_idx("fields",i));
					z=0;
					kl2++;
					temp=lr_paramarr_idx("views",1);
					temp1=lr_paramarr_idx("applets",ii);
					for (j=0;j<getcounter();j++) {
						m[j]=0;
					}
					sprintf(s2,"{%s_%s}",temp,temp1);
				}
			}
			if (lr_eval_string(s2)[0]!='1' || strcmp(lr_eval_string("{TypeApplets}"),status)==0) {
				f=0;
				c=lr_paramarr_idx("fields",i);
				for (j=1;j<=lr_paramarr_len("fieldmethod");j++) {
					b=lr_paramarr_idx("fieldnamemethod",j);
					if (strcmp(c,b)==0) {
						if (z==0) {
							z=1;
							y=j;
						}
						f=j;
						break;
					}
				}
				if (f==0) {
					if (lr_paramarr_idx("namefield",atoi(lr_paramarr_idx("fn",i)))[0]) {
						kl=atoi(lr_paramarr_idx("fn",i));
						sprintf(s,"{%s_%d}","namefield",kl);
						sprintf(st,"%s_%s_%s_%d",temp,temp1,lr_eval_string(s),m[kl]);
						lr_error_message ("%s;%s;%s_%d;%s;%s_%s_%s_%d",temp,temp1,lr_eval_string(s),m[kl],lr_paramarr_idx("fields",i),temp,temp1,lr_eval_string(s),m[kl]);
						if (kl>getcounter()) {
							lr_output_message("Случилось некое ..... и что-то работает неправильно. Либо косяк в скрипте, либо косяк в либе");
						}
						m[kl]++;
					} else {
						kl=atoi(lr_paramarr_idx("dn",i));
						sprintf(s,"{%s_%d}","namefield",kl);
						sprintf(st,"%s_%s_%s_%d",temp,temp1,lr_eval_string(s),m[kl]);
						lr_error_message ("%s;%s;%s_%d;%s;%s_%s_%s_%d",temp,temp1,lr_eval_string(s),m[kl],lr_paramarr_idx("fields",i),temp,temp1,lr_eval_string(s),m[kl]);
						if (kl>getcounter()) {
							lr_output_message("Случилось некое ..... и что-то работает неправильно. Либо косяк в скрипте, либо косяк в либе");
						}
						m[kl]++;
					}
				} else {
					kl3=0;
					for (j=y;j<f;j++) {
						if (strcmp(lr_paramarr_idx("fieldmethod",j),lr_paramarr_idx("fieldmethod",f))==0) {
							kl3++;
						}
					}
					sprintf(s,"{%s_%d}","fieldmethod",f);
					sprintf(st,"%s_%s_%s_%d",temp,temp1,lr_eval_string(s),kl3);
					lr_error_message ("%s;%s;%s_%d;%s;%s_%s_%s_%d",temp,temp1,lr_eval_string(s),kl3,lr_paramarr_idx("fields",i),temp,temp1,lr_eval_string(s),kl3);
				}
				sprintf(st1,"%s_%s_%s",temp,temp1,lr_paramarr_idx("fields",i));
				lr_save_string(lr_paramarr_idx("fields",i),st);
				lr_save_string(st,st1);
				//lr_output_message ("%s %s",lr_paramarr_idx("fields",i),st);
			}
		}
		free(m);
	}
	for (i=1;i<=lr_paramarr_len("applets");i++) {
		temp1=lr_paramarr_idx("applets",i);
		sprintf(s,"{%s_%s}",temp,temp1);
		if (lr_eval_string(s)[0]!='1' || strcmp(lr_eval_string("{TypeApplets}"),status)==0) {
			//flag=1;
			sprintf(s,"%s_%s",temp,temp1);
			lr_save_string("1",s);
		}
	}
}

void createparamforfieldsflag(int mainflag) {
	int i,k,kl1,num,kl,a,f,*m,kl2=1,j,kl3,z=1,y=1,flag=0,ii;
	int *m1;
	char st[500],*temp,s[1000],s2[300],s1[1000],st1[500],*temp1,*c,*b,status[10]="NewPopup";
	//long file;
	//file=fopen ("output.txt","a");
	temp=lr_paramarr_idx("views",1);
	lr_save_string(lr_eval_string("{applets1_count}"),"applets_count");
	for (i=1;i<=lr_paramarr_len("applets1");i++) {
		sprintf(st,"applets_%d",i);
		lr_save_param_regexp(lr_paramarr_idx("applets1",i), strlen(lr_paramarr_idx("applets1",i)), "RegExp=`ObjectName`(.*?)`", "Ordinal=All", "ResultParam=applets2", LAST);
		lr_save_string(lr_paramarr_idx("applets2",lr_paramarr_len("applets2")),st);
	}
	flag=mainflag;
	for (i=1;i<=lr_paramarr_len("applets");i++) {
		temp1=lr_paramarr_idx("applets",i);
		sprintf(s,"{%s_%s}",temp,temp1);
		if (lr_eval_string(s)[0]!='1' || strcmp(lr_eval_string("{TypeApplets}"),status)==0) {
			flag=1;
			//sprintf(s,"%s_%s",temp,temp1);
			//lr_save_string("1",s);
		}
	}
	temp1=lr_paramarr_idx("applets",kl2);
	sprintf(s2,"{%s_%s}",temp,temp1);
if (lr_eval_string("{Header}")[0] && (lr_eval_string("{flagforheader}")[0]=='0' || lr_eval_string("{flagforheader}")[0]=='2' || lr_eval_string("{flagforheader}")[0]=='1') || getcounter()==0) {
		lr_save_string(lr_eval_string("{Header}"),temp);
		getelemfromstring(lr_eval_string("{Header}"),"namefield");
	}
	if (flag==1) {
	//	m1=(int *)calloc(lr_paramarr_len("fieldmethod"),lr_paramarr_len,sizeof(int));
		m=(int *)calloc(getcounter(),sizeof(int));
		//lr_output_message("%d",getcounter());
		for (i=1;i<=lr_paramarr_len("fields");i++) {
			for (ii=1;ii<=lr_paramarr_len("fieldsnames");ii++) {
				if (strcmp(lr_paramarr_idx("fieldsnames",ii),lr_paramarr_idx("fields",i))==0) {
					//lr_output_message("%s %s",lr_paramarr_idx("fieldsnames",kl2+1),lr_paramarr_idx("fields",i));
					z=0;
					kl2++;
					temp=lr_paramarr_idx("views",1);
					temp1=lr_paramarr_idx("applets",ii);
					for (j=0;j<getcounter();j++) {
						m[j]=0;
					}
					sprintf(s2,"{%s_%s}",temp,temp1);
				}
			}
			if (mainflag==1 || lr_eval_string(s2)[0]!='1' || strcmp(lr_eval_string("{TypeApplets}"),status)==0) {
				f=0;
				c=lr_paramarr_idx("fields",i);
				for (j=1;j<=lr_paramarr_len("fieldmethod");j++) {
					b=lr_paramarr_idx("fieldnamemethod",j);
					if (strcmp(c,b)==0) {
						if (z==0) {
							z=1;
							y=j;
						}
						f=j;
						break;
					}
				}
				if (f==0) {
					if (lr_paramarr_idx("namefield",atoi(lr_paramarr_idx("fn",i)))[0]) {
						kl=atoi(lr_paramarr_idx("fn",i));
						sprintf(s,"{%s_%d}","namefield",kl);
						sprintf(st,"%s_%s_%s_%d",temp,temp1,lr_eval_string(s),m[kl]);
						lr_error_message ("%s;%s;%s_%d;%s;%s_%s_%s_%d",temp,temp1,lr_eval_string(s),m[kl],lr_paramarr_idx("fields",i),temp,temp1,lr_eval_string(s),m[kl]);
						if (kl>getcounter()) {
							lr_output_message("Случилось некое ..... и что-то работает неправильно. Либо косяк в скрипте, либо косяк в либе");
						}
						m[kl]++;
					} else {
						kl=atoi(lr_paramarr_idx("dn",i));
						sprintf(s,"{%s_%d}","namefield",kl);
						sprintf(st,"%s_%s_%s_%d",temp,temp1,lr_eval_string(s),m[kl]);
						lr_error_message ("%s;%s;%s_%d;%s;%s_%s_%s_%d",temp,temp1,lr_eval_string(s),m[kl],lr_paramarr_idx("fields",i),temp,temp1,lr_eval_string(s),m[kl]);
						if (kl>getcounter()) {
							lr_output_message("Случилось некое ..... и что-то работает неправильно. Либо косяк в скрипте, либо косяк в либе");
						}
						m[kl]++;
					}
				} else {
					kl3=0;
					for (j=y;j<f;j++) {
						if (strcmp(lr_paramarr_idx("fieldmethod",j),lr_paramarr_idx("fieldmethod",f))==0) {
							kl3++;
						}
					}
					sprintf(s,"{%s_%d}","fieldmethod",f);
					sprintf(st,"%s_%s_%s_%d",temp,temp1,lr_eval_string(s),kl3);
					lr_error_message ("%s;%s;%s_%d;%s;%s_%s_%s_%d",temp,temp1,lr_eval_string(s),kl3,lr_paramarr_idx("fields",i),temp,temp1,lr_eval_string(s),kl3);
				}
				sprintf(st1,"%s_%s_%s",temp,temp1,lr_paramarr_idx("fields",i));
				lr_save_string(lr_paramarr_idx("fields",i),st);
				lr_save_string(st,st1);
				//lr_output_message ("%s %s",lr_paramarr_idx("fields",i),st);
			}
		}
		free(m);
	}
	for (i=1;i<=lr_paramarr_len("applets");i++) {
		temp1=lr_paramarr_idx("applets",i);
		sprintf(s,"{%s_%s}",temp,temp1);
		if (lr_eval_string(s)[0]!='1' || strcmp(lr_eval_string("{TypeApplets}"),status)==0) {
			//flag=1;
			sprintf(s,"%s_%s",temp,temp1);
			lr_save_string("1",s);
		}
	}
}


void getparamsfield(char *view,char *applet,char *field) {
	char st[500];
	sprintf(st,"{%s_%s_%s}",view,applet,field);
	lr_output_message("%s %s %s  -  %s",view,applet,field,lr_eval_string(st));	
}