float * bubble(float * a, int m, int n)

     {

     char is=1;

     int i;

     float c;

       while(is)

       {   is=0;

           for (i=m+1; i<=n; i++)

           if ( a[i] < a[i-1] )

           {    c=a[i];

                a[i]=a[i-1];

                a[i-1]=c;

                is=1;

           }

       }

       return(a);

     }
