// Util.cpp is adapted from of the IP-Glasma solver.
// Copyright (C) 2018 Bjoern Schenke.
// Reproduced with permission by Mark Mace 2019 for Dilute-Dense gluon solver

#include "Util.h"
#include <iostream>

double ***Util::cube_malloc(int n1, int n2, int n3)
{
    //  cerr << "test1" << endl;
    int i,j,k,inc;
    double ***d1_ptr, *tmp_ptr;
    n1+=1;
    n2+=1;
    n3+=1;
    
    
    //    tmp_ptr = (double *) malloc(sizeof(double)*n1*n2*n3);
    //    tmp_ptr = new double[n1*n2*n3];
    
    // cerr << "test2" << endl;
    
    /* pointer to the n1*n2*n3 memory */
    
    //    d1_ptr = (double ***) malloc (sizeof(double **)*n1);
    d1_ptr = new double **[n1];
    // cerr << "test3" << endl;
    
    for(i=0; i<n1; i++)
    {
        //      d1_ptr[i] = (double **) malloc (sizeof(double *)*n2);
        d1_ptr[i] = new double *[n2];
    }
    //  cerr << "test4" << endl;
    
    for(i=0; i<n1; i++)
    {
        for(j=0; j<n2; j++)
        {
            // inc = n2*n3*i + n3*j;
            // d1_ptr[i][j] = &(tmp_ptr[inc]);
            d1_ptr[i][j] = new double [n3];
        }
    }
    //  cerr << "test5" << endl;
    
    for(i=0; i<n1; i++)
    {
        for(j=0; j<n2; j++)
        {
            for(k=0; k<n3; k++)
            {
                d1_ptr[i][j][k] = 0.0;
            }
        }
    }
    // cerr << "test6" << endl;
    
    return d1_ptr;
}/* cube_malloc */


void Util::cube_free(double ***cube, int n1, int n2, int n3)
{
    int i,j;
    n1+=1;
    n2+=1;
    n3+=1;
    
    
    for(i=0; i<n1; i++)
    {
        for(j=0; j<n2; j++)
        {
            // inc = n2*n3*i + n3*j;
            // d1_ptr[i][j] = &(tmp_ptr[inc]);
            delete [] cube[i][j];
        }
    }
    for(j=0; j<n2; j++)
    {
        delete [] cube[j];
    }
    
    delete [] cube;
    
}/* cube_free */


double **Util::mtx_malloc(int n1, int n2)
{
    int i, j;
    double **d1_ptr, *tmp_ptr;
    
    //    tmp_ptr = (double *)malloc(sizeof(double)*n1*n2);
    // tmp_ptr = new double[n1*n2];
    
    //    d1_ptr = (double **) malloc (sizeof(double *)*n1);
    d1_ptr = new double *[n1];
    
    for(i=0; i<n1; i++)
    {
        //      d1_ptr[i] = &(tmp_ptr[i*n2]);
        d1_ptr[i] = new double [n2];
    }
    
    for(i=0; i<n1; i++)
    {
        for(j=0; j<n2; j++)
        {
            d1_ptr[i][j] = 0.0;
        }
    }
    
    return d1_ptr;
}


void Util::mtx_free(double **m, int n1, int n2)
{
    int j;
    
    for(j=0; j<n2; j++)
    {
        delete [] m[j];
    }
    
    delete [] m;
    
}


double *Util::vector_malloc(int n1)
{
    double *d1_ptr;
    int i;
    
    /* pointer to the n1 array */
    //    d1_ptr = (double *) malloc (sizeof(double )*n1);
    d1_ptr = new double[n1];
    for(i=0; i<n1; i++) d1_ptr[i] = 0.0;
    
    return d1_ptr;
}


void Util::vector_free(double *vec)
{
    delete [] vec;
}

int **Util::int_mtx_malloc(int n1, int n2)
{
    int i,j,k;
    int ** d1_ptr;
    int * d2_ptr;
    
    
    /* pointer to the n1*n2 array */
    d2_ptr = (int *) malloc (sizeof(int)*n1*n2);
    
    /* pointer to the n1 array */
    d1_ptr = (int **) malloc (sizeof(int *)*n1);
    
    /* initialize */
    /* for each n2 vector, there is a pointer */
    /* hence there are n1 pointers */
    
    for(k=0; k<n1; k++) d1_ptr[k] = d2_ptr + k*n2;
    
    for(i=0; i<n1; i++)
    {
        for(j=0; j<n2; j++) d1_ptr[i][j] = 0;
    }
    return d1_ptr;
}


char **Util::char_mtx_malloc(int n1, int n2)
{
    int i,j,k;
    char ** d1_ptr;
    char * d2_ptr;
    
    
    /* pointer to the n1*n2 array */
    d2_ptr = (char *) malloc (sizeof(char)*n1*n2);
    
    /* pointer to the n1 array */
    d1_ptr = (char **) malloc (sizeof(char *)*n1);
    
    /* initialize */
    /* for each n2 vector, there is a pointer */
    /* hence there are n1 pointers */
    
    for(k=0; k<n1; k++) d1_ptr[k] = d2_ptr + k*n2;
    
    return d1_ptr;
}


char *Util::char_malloc(int n1)
{
    char *char_ptr;
    
    /* pointer to the n1 array */
    char_ptr = (char *) malloc (sizeof(char)*n1);
    //char_ptr = new char[n1];
    
    strcpy(char_ptr, "");
    return char_ptr;
}


void Util::char_free(char *vec)
{
    free(vec);
    //delete vec;
}

int *Util::int_malloc(int n1)
{
    int *d1_ptr;
    int i;
    
    /* pointer to the n1 array */
    d1_ptr = (int *) malloc (sizeof(int)*n1);
    
    for(i=0; i<n1; i++) d1_ptr[i] = 0;
    
    return d1_ptr;
}


double Util::Power(double x, int n)
{
    int i;
    double y;
    
    if(n == 0) return 1.0;
    
    y = 1.0;
    for(i=1; i<=n; i++) y *= x;
    
    return y;
}

double Util::sech(double x)
{
    return 1.0/cosh(x);
}/* sech */


int Util::is_yes_no(char *st)
{
    while ( (strcmp(st, "yes\0") != 0) && (strcmp(st, "no\0") != 0) )
    {
        printf("You must answer yes or no.\n");
        printf("Answer? : ");
        scanf("%s", st);
    }
    if(strcmp(st, "yes\0")==0) return 1;
    else if(strcmp(st, "no\0")==0) return 0;
}


void Util::itoa(int n, char *s)
{
    int i, sign;
    
    if( (sign = n) < 0 ) n = -n;
    
    i = 0;
    do{
        s[i++] = n % 10 + '0';
    } while( (n /= 10) > 0 );
    if(sign < 0) s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}


void Util::reverse( char *s)
{
    int i, j;
    char c;
    
    for(i=0, j = strlen(s)-1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


int Util::integer(double x)
{
    return (int)(x+0.49999);
}


void Util::prterr(char *s)
{
    fprintf(stderr, "%s", s);
}


int Util::count_lines(char *file_name)
{
    FILE *input;
    char ch;
    int count;
    
    input = fopen(file_name, "r");
    
    count = 0;
    while( (ch = getc(input)) != EOF )
    {
        if( ch == '\n' ) ++count;
    }
    fclose(input);
    
    return count;
}



double Util::Dot(double *x, double *y, int n)
{
    int i;
    double f;
    
    f = 0.0;
    for(i=1; i<=n; i++) f += x[i]*y[i];
    
    return f;
}


double Util::m4p(double *x, double *y)
{
    int i;
    double f;
    
    f = x[0]*y[0];
    for(i = 1; i<=3; i++) f -= x[i]*y[i];
    
    return f;
}/* m4p */


double Util::LinearPara(double nu, double max, double min, double *jacob)
{
    if(*jacob < 1.0e-100)
    {
        fprintf(stderr,
                "LinearPara: Jacob = %le. You must initialize Jacobian.\n", *jacob);
        fprintf(stderr, "Exiting...\n");
        exit(0);
    }
    if( (nu < 0.0) || (nu > 1.0) )
    {
        fprintf(stderr, "LinearPara: Nu = %le is out of the range.\n", nu);
        fprintf(stderr, "Exiting...\n");
        exit(0);
    }
    if(max < min)
    {
        fprintf(stderr, "LinearPara: max is smallter than min.\n");
        fprintf(stderr, "Exiting...\n");
        exit(0);
    }
    
    *jacob *= (max - min);
    return max*nu + min*(1.0 - nu);
}/* LinearPara */


int Util::IsFile(string file_name)
{
    static int isf;
    static int ind = 0;
    char st[80];
    FILE *temp;
    
    if( (temp = fopen(file_name.c_str(),"r")) == NULL) return 0;
    else
    {
        fclose(temp);
        return 1;
    }
}/* IsFile */


string Util::StringFind(string file_name, string st)
{
    string inputname = file_name;
    string tmpfilename;
    string str = st;
    
    string s;
    string xstr;
    
    tmpfilename = "input";
    
    int ind;
    static int flag = 0;
    if(flag == 0)
    {
        if(!IsFile(file_name))
        {
            cerr << "The file named " << file_name << " is absent." << endl;
            if(file_name == "")
            {
                cerr << "No input file name specified." << endl;
                exit(1);
            }
            else
            {
                cerr << "Creating " << tmpfilename << "..." << endl;
            }
            ofstream tmp_file(tmpfilename.c_str());
            tmp_file << "EndOfData" << endl;
            tmp_file.close();
        }/* if isfile */
        flag == 1;
    }/* if flag == 0 */
    
    ifstream input(inputname.c_str());
    
    input >> s;
    
    ind = 0;
    while(s.compare("EndOfData") != 0)
    {
        input >> xstr;
        if(s.compare(str) == 0)
        {
            ind++;
            input.close();
            return xstr;
        }/* if right, return */
        s.clear();
        input >> s;
    }/* while */
    
    input.close();
    
    if(ind == 0)
    {
        cerr << str << " not found in " << inputname << endl;
        cerr << "Create an input file." << endl;
        exit(1);
        return xstr;
    }
}/* StringFind */

char *Util::StringFind2(char *file_name, char *st)
{
    char *s;
    char *x;
    FILE *input, *tmp_file;
    int ind;
    static int flag = 0;
    
    
    if(flag == 0)
    {
        if(!IsFile(file_name))
        {
            fprintf(stderr, "The file named %s is absent.\n", file_name);
            if(file_name == NULL)
            {
                fprintf(stderr, "No input file name specified.\n");
                fprintf(stderr, "Creating a default file named input...\n");
                file_name = "input";
            }
            else
            {
                fprintf(stderr, "Creating %s..\n", file_name);
            }
            tmp_file = fopen(file_name,"w");
            fprintf(tmp_file, "EndOfData\n");
            fclose(tmp_file);
        }/* if isfile */
        flag == 1;
    }/* if flag == 0 */
    
    input = fopen(file_name,"r");
    
    cerr << "stringfind2" << endl;
    
    x = new char[80];
    
    cerr << "stringfind3" << endl;
    
    s = new char[80];
    
    string sstr;
    
    cerr << "stringfind4" << endl;
    
    fscanf(input, "%s", s);
    sstr = s;
    
    cerr << "stringfind5" << endl;
    
    ind = 0;
    while(sstr.compare("EndOfData") != 0)
    {
        fscanf(input, "%s", x);
        cerr << "stringfind6" << endl;
        if(strcmp(s, st) == 0)
        {
            ind++;
            fclose(input);
            //free(s);
            return x;
        }/* if right, return */
        //   free(s);
        //  s = char_malloc(80);
        fscanf(input, "%s", s);
    }/* while */
    
    
    
    fclose(input);
    
    if(ind == 0)
    {
        fprintf(stderr, "%s not found in %s.\n", st, file_name);
        printf("Enter %s = ", st);
        scanf("%s", x);
        printf("Rewriting %s...\n", file_name);
        ReWriteString(file_name, st, x);
        return x;
    }
    
}/* StringFind */


double Util::DFind(string file_name, string st)
{
    string s;
    double x;
    stringstream stm;
    s = StringFind(file_name, st);
    stm << s;
    stm >> x;
    return x;
}/* DFind */


int Util::IFind(string file_name, string st)
{
    double f;
    f = DFind(file_name, st);
    
    return (int) (f + 0.5);
}/* IFind */


void Util::ReWrite(char* file_name, char *st, double x)
{
    FILE *output, *input;
    char *s, c;
    double y;
    
    s = char_malloc(80);
    
    output = fopen("temp_temp.dat", "w");
    fprintf(output, "%s %lf\n", st, x);
    fclose(output);
    
    FileCat(file_name, "temp_temp.dat");
    
    FileCopy("temp_temp.dat", file_name);
    
    remove("temp_temp.dat");
    
    char_free(s);
}/* ReWrite */


void Util::ReWriteString(char *file_name, char *st, char *x)
{
    char c, *com, *str;
    double y;
    int i = 0;
    char template1[16];
    char tmp_file[16];
    FILE *output, *input;
    
    /* tmp_file = tmpnam(); this does not work with gcc */
    
    strcpy(tmp_file, "./tempXXXXX");
    // strcpy(template1, "./tempXXXXX");
    // tmp_file = mkdtemp(template1); /* this works with both cc and gcc */
    
    output = fopen(tmp_file, "w");
    
    fprintf(output, "%s %s\n", st, x);
    fclose(output);
    
    FileCat(file_name, tmp_file);
    FileCopy(tmp_file, file_name);
    
    remove(tmp_file);
    
}/* ReWriteString */


void Util::FileCopy(char *in_file, char *out_file)
{
    FILE *output, *input;
    char c;
    
    input = fopen(in_file, "r");
    output = fopen(out_file, "w");
    
    c = getc(input);
    while(c != EOF)
    {
        fprintf(output, "%c", c);
        c = getc(input);
    }
    
    fclose(input);
    fclose(output);
}/* FileCopy */


void Util::FileCat(char *in_file, char *out_file)
{
    FILE *output, *input;
    char c;
    
    input = fopen(in_file, "r");
    output = fopen(out_file, "a");
    
    c = getc(input);
    while(c != EOF)
    {
        fprintf(output, "%c", c);
        c = getc(input);
    }
    
    fclose(input);
    fclose(output);
}/* FileCopy */


int Util::IFindXInVx(double x, double *Vx, int ymax)
{
    int i, f, temp_i;
    static double *rmbr_Vx, minimum, maximum;
    static int ind = 0;
    static int mono_ind;
    
    ind++;
    if((ind == 1) || (rmbr_Vx != Vx))
    {
        ind = 1;
        rmbr_Vx = Vx;
        if(CheckMono(Vx, ymax, &temp_i) == 0)
        {
            fprintf(stderr, "IFindXInVx : Vx seems to be not monotonic.\n");
            fprintf(stderr, "Exiting...\n");
            exit(0);
        };
        mono_ind = temp_i;
    }
    
    maximum = maxi(Vx[0], Vx[ymax]);
    minimum = mini(Vx[0], Vx[ymax]);
    
    if( (x < minimum) || (x > maximum) )
    {
        fprintf(stderr, "IFindInVx : %e is out of the range [%e, %e].\n",
                x, minimum, maximum);
        fprintf(stderr, "Exiting...\n");
        exit(0);
    }/* if out of the range */
    
    if( mono_ind == 1 ) /* mono increasing */
    {
        i = 0;
        while((Vx[i] <= x) && i < ymax) i++;
        return ((fabs(Vx[i-1]-x) < fabs(Vx[i]-x)) ? i-1 : i);
    }/* mono increasing */
    else if( mono_ind == -1 ) /* mono decreasing */
    {
        i = ymax;
        while((Vx[i] <= x) && i > 0) i--;
        return ((fabs(Vx[i]-x) < fabs(Vx[i+1]-x)) ? i : i+1);
    }/* mono decreasing */
    
}/* IFindXInVx */

int Util::CheckMono(double *Vx, int ymax, int *mono_ind)
{
    int i, i_down, i_up;
    
    if(Vx[0] < Vx[ymax]) *mono_ind = 1; /* increasing */
    else *mono_ind = -1; /* decreasing */
    
    if(*mono_ind == 1)
    {
        for(i=0; i<ymax; i++)
        {
            if(Vx[i] > Vx[i+1]) return 0; /* not monotonic */
        }/* for */
    }/* if */
    else if(*mono_ind == -1)
    {
        for(i=ymax; i>0; i--)
        {
            if(Vx[i] > Vx[i-1]) return 0; /* not monotonic */
        }/* for */
    }/* else if */
    
    return 1;
}/* CheckMono */


void Util::Shout()
{
    static int ind = 0;
    
    ind++;
    
    fprintf(stderr, "Shouting %d\n", ind);
}/* Shout */




// void Util::InBin(double x, double xdown, double xup, double inc, double *num)
// {
//  if( (xdown <= x) && (x < xup) ) *num += inc;
// }/* InBin */

// double Util::VAve(double *v, int min, int max)
// {
//  int i;
//  double sum, f;

//  if( max < min) return 0.0;

//  sum = 0.0;
//  for(i=min; i<=max; i++) sum += v[i];

//  f= sum/(max-min+1);
//  fprintf(stderr, "VAve = %le\n", f);
//  return f;
// }/* VAve */


// double Util::VStdDev(double *v, int min, int max)
// {
//  int i;
//  double sum, sum2, ave, f;

//  if(max <= min) return 0.0;

//  ave = VAve(v, min, max);

//  sum = sum2 = 0.0;
//  for(i=min; i<=max; i++)
//   {
//    sum += (v[i] - ave);
//    sum2 += (v[i] - ave)*(v[i]-ave);
//   }

//  f = (sum2 - sum*sum/(max-min+1.0))/(max-min);
//  fprintf(stderr, "VStdAve2 = %le\n", f);

//  f = sqrt(fabs(f));
//  fprintf(stderr, "VStdAve = %le\n", f);
//  return f;
// }/* VStdDev */


double Util::d_read_in(char *s)
{
    double x;
    fprintf(stderr, "(Double) Value of %s = ", s);
    scanf("%lf", &x);
    return x;
}

int Util::i_read_in(char *s)
{
    int i;
    fprintf(stderr, "(Integer) Value of %s = ", s);
    scanf("%d", &i);
    return i;
}


char *Util::ch_read_in(char *s)
{
    char *str;
    
    str = char_malloc(80);
    fprintf(stderr, "(String) Value of %s = ", s);
    scanf("%s", str);
    return str;
}


void Util::CountTime(int i, int inc1, int inc2, int last)
{
    if(i % inc1 == 0) fprintf(stderr, "%d ", i);
    if(i % inc2 == 0) fprintf(stderr, "\n");
    if( (i == last) )
    {
        fprintf(stderr, "\nDone with this loop.\n");
    }
}


int *Util::heapSort(double *numbers, int array_size)
{
    int i, itemp;
    static int *re_arrange;
    double temp;
    
    re_arrange = int_malloc(array_size+1);
    for(i=0; i<array_size; i++) re_arrange[i] = i;
    
    for (i = (array_size / 2)-1; i >= 0; i--)
    siftDown(numbers, i, array_size, re_arrange);
    
    for (i = array_size-1; i >= 1; i--)
    {
        temp = numbers[0];
        numbers[0] = numbers[i];
        numbers[i] = temp;
        
        itemp = re_arrange[0];
        re_arrange[0] = re_arrange[i];
        re_arrange[i] = itemp;
        
        siftDown(numbers, 0, i-1, re_arrange);
    }
    
    return re_arrange;
}


int Util::siftDown(double *numbers, int root, int bottom, int *re_arrange)
{
    int done, maxChild, itemp;
    double temp;
    
    done = 0;
    while ((root*2 <= bottom) && (!done))
    {
        if (root*2 == bottom)
        maxChild = root * 2;
        else if (numbers[root * 2] > numbers[root * 2 + 1])
        maxChild = root * 2;
        else
        maxChild = root * 2 + 1;
        
        if (numbers[root] < numbers[maxChild])
        {
            temp = numbers[root];
            numbers[root] = numbers[maxChild];
            numbers[maxChild] = temp;
            
            itemp = re_arrange[root];
            re_arrange[root] = re_arrange[maxChild];
            re_arrange[maxChild] = itemp;
            
            root = maxChild;
        }
        else
        done = 1;
    }
    return done;
}/* siftDown */


double Util::Theta(double x, double a)
{
    double f;
    
    if(a==0.0)
    {
        if(x < 0.0) return 0.0;
        else if(x > 0.0) return 1.0;
        else return 0.5;
    }
    else
    {
        f = 1.0 + tanh(x/a);
        f *= 0.5;
        return f;
    }
}/* Theta */

/* nrutil.c */
/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
/* nrutil.c */
void Util::nrerror(char error_text[])
/* Numerical Recipes standard error handler */
{
    
    fprintf(stderr,"Numerical Recipes run-time error...\n");
    fprintf(stderr,"%s\n",error_text);
    fprintf(stderr,"...now exiting to system...\n");
    exit(1);
}

float *Util::vector(int nl, int nh)
/* allocate a float vector with subscript range v[nl..nh] */
{
    float *v;
    
    v=(float *)malloc((unsigned) (nh-nl+1)*sizeof(float));
    if (!v) nrerror("allocation failure in vector()");
    return v-nl;
}

int *Util::ivector(int nl, int nh)
/* allocate an int vector with subscript range v[nl..nh] */
{
    int *v;
    
    v=(int *)malloc((unsigned) (nh-nl+1)*sizeof(int));
    if (!v) nrerror("allocation failure in ivector()");
    return v-nl;
}

double *Util::dvector(int nl, int nh)
/* allocate a double vector with subscript range v[nl..nh] */
{
    double *v;
    
    v=(double *)malloc((unsigned) (nh-nl+1)*sizeof(double));
    if (!v) nrerror("allocation failure in dvector()");
    return v-nl;
}

float **Util::matrix(int nrl, int nrh, int ncl, int nch)
/* allocate a float matrix with subscript range m[nrl..nrh][ncl..nch] */
{
    int i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
    float **m;
    
    /* allocate pointers to rows */
    m=(float **) malloc((unsigned)(nrow*sizeof(float*)));
    if (!m) nrerror("allocation failure 1 in matrix()");
    m -= nrl;
    
    /* allocate rows and set pointers to them */
    m[nrl]=(float *) malloc((unsigned)(nrow*ncol*sizeof(float)));
    if (!m[nrl]) nrerror("allocation failure 2 in matrix()");
    
    for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
    
    /* return pointer to array of pointers to rows */
    return m;
}

double **Util::dmatrix(int nrl, int nrh, int ncl, int nch)
/* allocate a double matrix with subscript range m[nrl..nrh][ncl..nch] */
{
    int i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
    double **m;
    
    /* allocate pointers to rows */
    m=(double **) malloc((unsigned)(nrow*sizeof(double*)));
    if (!m) nrerror("allocation failure 1 in matrix()");
    m -= nrl;
    
    /* allocate rows and set pointers to them */
    m[nrl]=(double *) malloc((unsigned)(nrow*ncol*sizeof(double)));
    if (!m[nrl]) nrerror("allocation failure 2 in matrix()");
    
    for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
    
    /* return pointer to array of pointers to rows */
    return m;
}

int **Util::imatrix(int nrl, int nrh, int ncl, int nch)
/* allocate a int matrix with subscript range m[nrl..nrh][ncl..nch] */
{
    int i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
    int **m;
    
    /* allocate pointers to rows */
    m=(int **) malloc((unsigned)(nrow*sizeof(int*)));
    if (!m) nrerror("allocation failure 1 in matrix()");
    m -= nrl;
    
    /* allocate rows and set pointers to them */
    m[nrl]=(int *) malloc((unsigned)(nrow*ncol*sizeof(int)));
    if (!m[nrl]) nrerror("allocation failure 2 in matrix()");
    
    for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
    
    /* return pointer to array of pointers to rows */
    return m;
}

float **Util::submatrix(float **a, int oldrl, int oldrh, int oldcl, int oldch, int newrl, int newcl)
/* point a submatrix [newrl..][newcl..] to a[oldrl..oldrh][oldcl..oldch] */
{
    int i,j,nrow=oldrh-oldrl+1,ncol=oldcl-newcl;
    float **m;
    
    /* allocate array of pointers to rows */
    m=(float **) malloc((unsigned) (nrow*sizeof(float*)));
    if (!m) nrerror("allocation failure in submatrix()");
    m -= newrl;
    
    /* set pointers to rows */
    /*	m[newrl]=a[oldr1];
     for(i=oldrl,j=newrl+1;i<=oldrh;i++,j++) m[j]=m[j-1]+a[i]+ncol;*/
    for(i=oldrl,j=newrl;i<=oldrh;i++,j++) m[j]=a[i]+ncol;
    
    /* return pointer to array of pointers to rows */
    return m;
}

float **Util::convert_matrix(float *a, int nrl, int nrh, int ncl, int nch)
/* allocate a float matrix m[nrl..nrh][ncl..nch] that points to the matrix
 declared in the standard C manner as a[nrow][ncol], where nrow=nrh-nrl+1
 and ncol=nch-ncl+1. The routine should be called with the address
 &a[0][0] as the first argument. */
{
    int i,j,nrow=nrh-nrl+1,ncol=nch-ncl+1;
    float **m;
    
    /* allocate pointers to rows */
    if ((m=(float **) malloc((unsigned) (nrow*sizeof(float*)))) == NULL)
    nrerror("allocation failure in convert_matrix()");
    m -= nrl;
    
    /* set pointers to rows */
    m[nrl]=a-ncl;
    for(i=1,j=nrl+1;i<nrow;i++,j++) m[j]=m[j-1]+ncol;
    /* return pointer to array of pointers to rows */
    return m;
}

void Util::free_vector(float *v, int nl, int nh)
/* free a float vector allocated with vector() */
{
    free((char*) (v+nl));
}

void Util::free_ivector(int *v, int nl, int nh)
/* free an int vector allocated with ivector() */
{
    free((char*) (v+nl));
}

void Util::free_dvector(double *v, int nl, int nh)
/* free a double vector allocated with dvector() */
{
    free((char*) (v+nl));
}

void Util::free_matrix(float **m, int nrl, int nrh, int ncl, int nch)
/* free a float matrix allocated by matrix() */
{
    free((char*) m[nrl]);
    free((char*) (m+nrl));
}

void Util::free_dmatrix(double **m, int nrl, int nrh, int ncl, int nch)
/* free a double matrix allocated by dmatrix() */
{
    free((char*) m[nrl]);
    free((char*) (m+nrl));
}

void Util::free_imatrix(int **m, int nrl, int nrh, int ncl, int nch)
/* free an int matrix allocated by imatrix() */
{
    free((char*) m[nrl]);
    free((char*) (m+nrl));
}

void Util::free_submatrix(float **b, int nrl, int nrh, int ncl, int nch)
/* free a submatrix allocated by submatrix() */
{
    free((char*) (b+nrl));
}

void Util::free_convert_matrix(float **b, int nrl, int nrh, int ncl, int nch)
/* free a matrix allocated by convert_matrix() */
{
    free((char*) (b+nrl));
}



#define MAX_SEARCH 100000
/* This returns s between s_down and s_up that satisfies */
/* func(s) = nu */

double Util::Solve
(double nu, double (*func)(double),
 double s_down, double s_up, double tol, int *count)
{
    double s_mid, fmid, diff, maximum, minimum;
    int ind;
    
    /* whenever Solve is invoked, count up */
    
    *count += 1;
    
    if(*count > MAX_SEARCH)
    {
        fprintf(stderr, "Solve: Exceeding maximum search allowed.  Exiting...\n");
        exit(0);
    }
    
    if(nu == (*func)(s_down)) return s_down;
    if(nu == (*func)(s_up)) return s_up;
    
    maximum =
    ( (*func)(s_up) > (*func)(s_down) ? (*func)(s_up) : (*func)(s_down) );
    minimum =
    ( (*func)(s_up) < (*func)(s_down) ? (*func)(s_up) : (*func)(s_down) );
    
    if( (nu > maximum) || (nu < minimum) )
    {
        fprintf(stderr, "Solve: Unable to search %le .\n", nu);
        fprintf(stderr, "\nEither the search parameter %le is out of the range, \n",
                nu);
        fprintf(stderr, "or the function is NOT monotonic.\n\n");
        fprintf(stderr, "maximum = %le\n", maximum);
        fprintf(stderr, "minimum = %le\n", minimum);
        fprintf(stderr, "count = %d\n", *count);
        
        exit(0);
    }
    
    s_mid = (s_up + s_down)/2.0;
    fmid = (*func)(s_mid);
    
    /* deal with exceptions */
    
    ind = ( ((*func)(s_up) > (*func)(s_down)) ? 1 : -1);
    if(nu != 0.0) diff = (fmid-nu)/nu;
    else if( (nu == 0.0) && (fmid != 0.0) ) diff = (fmid-nu)/fmid;
    else if( (nu == 0.0) && (fmid == 0.0) ) return s_mid;
    
    if( fabs(diff) < tol ) return s_mid;
    else if( (fmid > nu) && ind == 1)
    {
        /* if increasing function, and s_mid gives you larger value */
        /* then s is in the smaller part */
        
        return Solve(nu, func, s_down, s_mid, tol, count);
    }
    else if( (fmid < nu) && ind == 1)
    {
        /* if increasing function, and s_mid gives you smaller value */
        /* then s is in the larger part */
        
        return Solve(nu, func, s_mid, s_up, tol, count);
    }
    else if( (fmid > nu) && ind == -1)
    {
        /* if decreasing function and s_mid gives you larger value */
        /* then s is in the larger part */
        
        return Solve(nu, func, s_mid, s_up, tol, count);
    }
    else if( (fmid < nu) && ind == -1)
    {
        /* if decreasing function, and s_mid gives you smaller value */
        /* then s is in the smaller part */
        
        return Solve(nu, func, s_down, s_mid, tol, count);
    }
}/* Solve */
#undef MAX_SEARCH


int Util::NumCol(char *infile)
{
    FILE *input;
    char ch, prev_ch;
    int num_cols;
    
    input = fopen(infile, "r");
    num_cols = 0;
    
    prev_ch = ' ';
    while( (ch = getc(input)) != '\n')
    {
        if( (prev_ch == ' ') || (prev_ch == '	') )
        {
            if( (ch != ' ') && (ch != '	') )
            {
                num_cols++;
            }
        }/* if prev_ch */
        prev_ch = ch;
    }
    fclose(input);
    
    fprintf(stderr, "Number of Columns in %s = %d\n", infile, num_cols);
    
    return num_cols;
}/* NumCol */

int Util::binning(double x, double xi, double xf, double *bins, int num_bins)
{
    double dx;
    int i;
    dx = (xf-xi)/(num_bins);
    
    i = (int)((x-xi)/dx);
    
    if( (0 <= i) && (i < num_bins) )
    { bins[i] += 1.0;
        return i;}
    else
    {
        //        fprintf(stderr, "binning i = %d\n", i);
        return -1;
    }
}

void Util::InBinLocal(double x, double xdown, double xup, double inc, double *num)
{
    if( (xdown <= x) && (x < xup) ) *num += inc;
}/* InBinLocal */


double Util::lin_int(double x1,double x2,double f1,double f2,double x)
{
    double aa, bb;
    
    if (x2 == x1)
    aa = 0.0;
    else
    aa =(f2-f1)/(x2-x1);
    bb = f1 - aa * x1;
    
    return aa*x + bb;
}

/* Test program */
/*
 main()
 {
 double x, f, jacob, *Vx;
 int i, j, mono_ind;
 
 Vx = vector_malloc(101);
 
 jacob = 1.0;
 for(i=0; i<=100; i++)
 {
 Vx[i] = 15000.0-(i*30.0 + i*i*1.0);
 fprintf(stderr, "%le\n", Vx[i]);
 }
 
 fprintf(stderr, "checkmono = %d\n", CheckMono(Vx, 100, &mono_ind));
 fprintf(stderr, "mono_ind %d\n", mono_ind);
 
 for(i=0; i<3; i++)
 {
 printf("Enter x = ");
 scanf("%lf", &x);
 
 j = IFindXInVx(x, Vx, 100);
 
 printf("j = %d\n", j);
 printf("Vj = %lf\n", Vx[j]);
 printf("Vj+1 = %lf\n", Vx[j+1]);
 printf("Vj-1 = %lf\n", Vx[j-1]);
 }
 
 Vx = vector_malloc(101);
 jacob = 1.0;
 for(i=0; i<=100; i++)
 {
 Vx[i] = (i*30.0 + i*i*1.0);
 fprintf(stderr, "%le\n", Vx[i]);
 }
 
 fprintf(stderr, "checkmono = %d\n", CheckMono(Vx, 100, &mono_ind));
 fprintf(stderr, "mono_ind %d\n", mono_ind);
 
 for(i=0; i<3; i++)
 {
 printf("Enter x = ");
 scanf("%lf", &x);
 
 j = IFindXInVx(x, Vx, 100);
 
 printf("j = %d\n", j);
 printf("Vj = %lf\n", Vx[j]);
 printf("Vj+1 = %lf\n", Vx[j+1]);
 printf("Vj-1 = %lf\n", Vx[j-1]);
 }
 }
 */
