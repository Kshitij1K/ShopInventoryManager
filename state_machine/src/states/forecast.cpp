#include <iostream>
#include <vector>

namespace forecaster{
    std::vector<long double> update_smoothed_error(double alpha, std::vector<long double> smoothed_error_prev, std::vector<long double>forecast_prev, std::vector<long double>demand_prev  ){
        std::vector<long double> smoothed_error;
        long long n = smoothed_error_prev.size();
        for (int i =0; i<n;i++){
            long double error = demand_prev[i]-forecast_prev[i];
            smoothed_error.push_back(alpha*error + (1-alpha)*(smoothed_error_prev[i]) );
        }
        return(smoothed_error);
    }

    std::vector<long double> update_MADt(double alpha, std::vector<long double> MADt_prev, std::vector<long double> forecast_prev, std::vector<long double> demand_prev){
        std::vector<long double> MADt;
        long long n = MADt_prev.size();
        for (int i=0; i<n; i++){
            long double error = demand_prev[i]-forecast_prev[i];
            if(error<0){
                error = -error;
            }
            MADt.push_back(alpha*error + (1-alpha)*(MADt_prev[i]));
        }
        return(MADt);
    }

    std::vector<long double> T_calculater(std::vector<long double> smoothed_error, std::vector<long double> MADt){
        long long n = MADt.size();
        std::vector<long double> T;
        for (int i =0; i<n; i++){
            T.push_back(smoothed_error[i]/MADt[i]);
        }
        return(T);
    }

    std::vector<long double> forecast(std::vector<long double> smoothed_error, std::vector<long double> MADt, std::vector<long double> forecast_prev, std::vector<long double> demand_prev, std::vector<long double> T){
        std::vector<long double> forecast_new;
        long long n = smoothed_error.size();
        for (int i=0; i<n; i++){
            long double T_coeff = T[i];
            if(T_coeff<0){
                T_coeff = -T_coeff;
            }
            long double error = demand_prev[i] - forecast_prev[i];
            forecast_new.push_back(forecast_prev[i] + T_coeff*error);
        }
        return(forecast_new);
    }

}