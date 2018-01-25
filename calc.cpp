void calculate(double a, double mu, int v, int n, double* pk, double* pt, double* pv, double* k, double* t)
{

  double numenator = 0;
  double denumerator = 0;
  //
  double combination = 1;
  double fraction = 1;
  //

  for(int i = 0; i<=v; i++)
  {
    denumerator+=combination*fraction;
    combination*=((double)n-i)/(i+1);
    fraction*=a/(1-a);
  }

  combination = 1;
  fraction = 1;

  for(int i = 0; i<=v; i++)
  {
      pk[i] = (combination*fraction)/denumerator;
      combination*=((double)n-i)/(i+1);
      fraction*=a/(1-a);
  }

    *pt = pk[v];

    denumerator = 0;
    combination = 1;
  fraction = 1;
  //

  for(int i = 0; i<=v; i++)
  {
    denumerator+=combination*fraction;
    combination*=((double)(n-1)-(double)i)/(i+1);
    fraction*=a/(1-a);
  }

  combination = 1;
  fraction = 1;

  for(int i = 0; i<=v; i++)
  {
      combination*=((double)(n-1)-(double)i)/(i+1);
//          std::cout << "combination = " << combination <<  " " << i << std::endl;
      fraction*=a/(1-a);
  }


//    std::cout << "fraction = " << fraction << std::endl;
//    std::cout << "denumerator = " << denumerator << std::endl;
    *pv = combination*fraction/denumerator;

    for(int i=0; i<=v; i++)
    {
      *k+=i*pk[i];
    }

    *t = *k/(n-*k)/(mu*a/(1-a));

    /*for(int i =0; i<=v; i++)
    {
      std::cout << "pk[" << i<< "] = " << pk[i] << std::endl;
    }*/
}
