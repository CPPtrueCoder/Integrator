#include "dormand_prince.h"
#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;
dormand_prince::dormand_prince(long double eps_, long double eps_max_,
                               long double h_, long double new_h_, int n_,
                               long double delta_, int size_) {
  delta = delta_;
  eps = eps_;
  eps_max = eps_max_;
  h = h_;
  new_h = new_h_;
  n = n_;
  k = new long double *[7];
  for (int i = 0; i < 7; i++) {
    k[i] = new long double[n];
  }
  b = new long double *[6];
  for (int i = 0; i < 6; i++) {
    b[i] = new long double[n];
  }
  size = size_;
  result_list = new long double *[size];
  for (int i = 0; i < size; i++) {
    result_list[i] = new long double[n + 1];
  }
}
long double dormand_prince::eps_(long double *a1, long double *a4,
                                 long double *a5) {
  long double sum = 0;
  long double u = 1;
  while (1 + u > 1)
    u /= 2;
  // cout << u << endl;
  for (int i = 0; i < n; i++) {
    long double part =
        fabs(a4[i] - a5[i]) / (fmax(fmax(pow(10, -5), fabs(a4[i])),
                                    fmax(fabs(a1[i]), 2. * u / eps_max)));
    part = pow(part, 2);
    sum += part;
  }
  sum /= n;
  sum = sqrt(sum);
  sum *= h;
  return sum;
}
long double dormand_prince::h_new(long double eps) {
  return h / fmax(0.1, fmin(5., pow(eps / eps_max, 0.2) / 0.9));
}
long double *dormand_prince::integration(long double t_start,
                                         long double t_finish,
                                         Object *example) {
  // long double t_out = t_start;
  static int counter = 0;
  long double t = t_start;
  long double *a1 = new long double[n];
  long double *a4 = new long double[n];
  long double *a5 = new long double[n];
  long double *ind = new long double[n];
  long double *dep = new long double[n];
  long double *step_result = new long double[n];
  long double b[6];
  // int size = (int)((t_finish - t_start) / delta);
  ofstream fout;
  static int cycle = 0;
  fout.open("a.txt");
  int output_counter = 0;
  // long double new_h = delta;
  long double sum = 0;
  long double t_out = t_start;
  long double u = 1.0l;
  while (1.0l + u > 1.0l)
    u /= 2.l;
  cout << u << endl;
  // eps_max = u;
  // cout << u << endl;
  /*for (int i = 0; i < n; i++)
  {
          std::cout << example->function(NULL, NULL)[i] << std::endl;
          //std::cout << a1[i] << std::endl;
  }*/
  int local_counter = 0;
  new_h = 1;
  long double T = 17.0652165601579625588917206249L;
  for (int i = 0; i < n; i++) {
    a1[i] = example->GetA_I(i);
  }
  // new_h = 1e-16;
  for (int i = 0; i < n; i++)
    cout << a1[i] << endl;
  while (t < t_finish) {
    local_counter++;
    counter++;
    // cout << local_counter << endl;
    h = new_h;
    if (t + h > t_finish)
      h = t_finish - t;
    // std::cout << h << std::endl;

    /*for (int i = 0; i < 7; i++)
    {
            for (int j = 0; j < n; j++)
            {
                    ind[j] = t + c[i] * h;
                    if (i > 0)
                    {
                            for (int s = 0; s < i; s++)
                            {
                                    sum += a[i][s] * k[s][j];
                            }
                    }
                    sum *= h;
                    //std::cout <<"sum="<< sum << std::endl;
                    dep[j] = a1[j] + sum;

                    sum = 0;
            }
            example->function(ind, dep,step_result);
            for (int j = 0; j < n; j++)
            {
                    k[i][j] = step_result[j];
                    //std::cout <<"k"<<i<<j<<"="<< k[i][j] << std::endl;
            }
    }*/
    /*if (output_counter > 0)
    {
            for (int i = 0; i < n; i++) k[0][i] = a1[i];
    }
    else
    {
            for (int i = 0; i < n; i++)
            {
                    ind[i] = t + h * c[0];
                    dep[i] = a1[i];
            }
            example->function(ind, dep, step_result);
            for (int i = 0; i < n; i++) k[0][i] = step_result[i];
            delete[] ind;
            delete[] dep;
            delete[] step_result;
            ind = new double[n];
            dep = new double[n];
            step_result = new double[n];
    }*/
    for (int i = 0; i < n; i++) {
      ind[i] = t + h * c[0];
      dep[i] = a1[i] + 0;
    }
    example->function(ind, dep, step_result);
    for (int i = 0; i < n; i++)
      k[0][i] = step_result[i];

    // for (int i = 0; i < n; i++) k[0][i] = a1[i];
    for (int i = 0; i < n; i++) {
      ind[i] = t + h * c[1];
      dep[i] = a1[i] + h * (k[0][i] * a[1][0]);
    }
    example->function(ind, dep, step_result);
    for (int i = 0; i < n; i++)
      k[1][i] = step_result[i];

    for (int i = 0; i < n; i++) {
      ind[i] = t + h * c[2];
      dep[i] = a1[i] + h * (k[0][i] * a[2][0] + k[1][i] * a[2][1]);
    }
    example->function(ind, dep, step_result);
    for (int i = 0; i < n; i++)
      k[2][i] = step_result[i];

    for (int i = 0; i < n; i++) {
      ind[i] = t + h * c[3];
      dep[i] = a1[i] +
               h * (k[0][i] * a[3][0] + k[1][i] * a[3][1] + k[2][i] * a[3][2]);
    }
    example->function(ind, dep, step_result);
    for (int i = 0; i < n; i++)
      k[3][i] = step_result[i];

    for (int i = 0; i < n; i++) {
      ind[i] = t + h * c[4];
      dep[i] = a1[i] + h * (k[0][i] * a[4][0] + k[1][i] * a[4][1] +
                            k[2][i] * a[4][2] + k[3][i] * a[4][3]);
    }
    example->function(ind, dep, step_result);
    for (int i = 0; i < n; i++)
      k[4][i] = step_result[i];

    step_result = new long double[n];
    for (int i = 0; i < n; i++) {
      ind[i] = t + h * c[5];
      dep[i] = a1[i] +
               h * (k[0][i] * a[5][0] + k[1][i] * a[5][1] + k[2][i] * a[5][2] +
                    k[3][i] * a[5][3] + k[4][i] * a[5][4]);
    }
    example->function(ind, dep, step_result);
    for (int i = 0; i < n; i++)
      k[5][i] = step_result[i];

    for (int i = 0; i < n; i++) {
      ind[i] = t + h * c[6];
      dep[i] = a1[i] +
               h * (k[0][i] * a[6][0] + k[1][i] * a[6][1] + k[2][i] * a[6][2] +
                    k[3][i] * a[6][3] + k[4][i] * a[6][4] + k[5][i] * a[6][5]);
    }
    example->function(ind, dep, step_result);
    for (int i = 0; i < n; i++)
      k[6][i] = step_result[i];
    long double *test = new long double[n];
    for (int i = 0; i < n; i++) {
      a4[i] = 0;

      a5[i] = 0;
      // std::cout << a4[i] << " " << a5[i] << std::endl;
      /*for (int j = 0; j < 6; j++)
      {
              a4[i] += h * b1[j] * k[j][i];
      }
      for (int j = 0; j < 7; j++)
      {
              a5[i] += h * b2[j] * k[j][i];
      }*/

      a4[i] = a1[i] + h * (b1[0] * k[0][i] + b1[1] * k[1][i] + b1[2] * k[2][i] +
                           b1[3] * k[3][i] + b1[4] * k[4][i] + b1[5] * k[5][i]);
      a5[i] = a1[i] + h * (b2[0] * k[0][i] + b2[1] * k[1][i] + b2[2] * k[2][i] +
                           b2[3] * k[3][i] + b2[4] * k[4][i] + b2[5] * k[5][i] +
                           b2[6] * k[6][i]);
      // std::cout << a4[i] << " " << a5[i] << std::endl;
    }

    /*for (int j = 0; j < n; j++)
    {
            std::cout << "a4 a5" << a4[j] << " " << a5[j] << std::endl;
    }*/
    eps = eps_(a1, a4, a5);
    // cout << eps << endl;
    new_h = h_new(eps);
    /*long double summ = 0;
    long double a = fmax(1e-05l, 2.l * u / eps_max);
    for (int i = 0; i < n; i++)
    {
            long double b = fmax(fabs(a1[i]), fabs(a4[i]));
            summ += pow(h*fabs(a4[i] - a5[i])/fmax(a,b),2);
    }
    summ /= n;
    summ = sqrt(summ);*/
    /*long double summ = 0;
    for (int i = 0; i < n; i++)
    {
            long double part = h * fabs(a4[i] - a5[i]) / (fmax(fmax(pow(10, -5),
    fabs(a4[i])), fmax(fabs(a1[i]), 2. * u / eps_max))); part = pow(part, 2);
            summ += part;
    }
    summ /= n;
    summ = sqrt(summ);*/
    // eps = summ;
    /*std::cout << eps << std::endl;*/
    //
    /*summ = 0;
    summ = h / fmax(0.1l, fmin(5.l, pow(eps / eps_max, 0.2l) / 0.9l));
    new_h = summ;
            //std::cout << h << std::endl;*/
    if (eps > eps_max) {
      cycle++;
      continue;
    }
    while ((t_out < t + h) && (t_out <= t_finish)) {
      long double theta = (t_out - t) / h;
      // long double* result = (long double*)malloc((n + 1) * sizeof(long
      // double));
      for (int i = 0; i < n; i++) {
        b[0] = theta * (1.l + theta * (-1337.l / 480.l +
                                       theta * (1039.l / 360.l +
                                                theta * (-1163.l / 1152.l))));
        b[1] = 0;
        b[2] = 100.l * pow(theta, 2.l) *
               (1054.l / 9275.l +
                theta * (-4682.l / 27825.l + theta * (379.l / 5565.l))) /
               3.l;
        b[3] = -5.l * pow(theta, 2.l) *
               (27.l / 40.l + theta * (-9.l / 5.l + theta * (83.l / 96.l))) /
               2.l;
        b[4] =
            18225.l * pow(theta, 2.l) *
            (-3.l / 250.l + theta * (22.l / 375.l + theta * (-37.l / 600.l))) /
            848.l;
        b[5] =
            -22.l * pow(theta, 2.l) *
            (-3.l / 10.l + theta * ((29.l / 30.l) + theta * (-17.l / 24.l))) /
            7.l;
        long double su = 0;
        for (int j = 0; j < 6; j++) {
          su += b[j] * k[j][i];
        }
        result_list[output_counter][i] = a1[i] + h * su;
        // cout << su << endl;
      }
      result_list[output_counter][n] = t_out;
      // cout << t_out<< endl;
      t_out += delta;
      output_counter++;
    }
    local_counter = 0;
    // for (int i = 0; i < n; i++) std::cout << example->GetA()[i] << std::endl;
    t += h;
    for (int i = 0; i < n; i++) {
      fout << a1[i] << " ";
      a1[i] = a4[i];
      // example->SetA(a5);
      // cout << a1[i] << " ";
    }
    // cout << endl;
    fout << h << " ";
    fout << t << endl;
  }
  cout << cycle << endl;
  std::cout << counter << std::endl;
  return a5;
}
void dormand_prince::plotter(int k, int l, int size) {

  FILE *pipe = _popen("B:/gnuplot/bin/gnuplot.exe", "w");
  if (pipe != nullptr) {
    fprintf(pipe, "set term win\n");

    system("pause");

    fprintf(pipe, "plot '-' with lines\n");
    for (int i = 0; i < size; i++)
      fprintf(pipe, "%lf %lf\n", (double)result_list[i][k],
              (double)result_list[i][2]);
    fprintf(pipe, "%s\n", "e");

    fflush(pipe);
  } else
    puts("Could not open the file\n");
  system("pause");
  if (pipe)
    _pclose(pipe);

  system("pause");
}
