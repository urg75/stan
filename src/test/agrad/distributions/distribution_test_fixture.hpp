#ifndef __TEST__AGRAD__DISTRIBUTIONS__DISTRIBUTION_TEST_FIXTURE_HPP___
#define __TEST__AGRAD__DISTRIBUTIONS__DISTRIBUTION_TEST_FIXTURE_HPP___

#ifndef _LOG_PROB_
#define _LOG_PROB_ MUST_DEFINE_LOG_PROB
#endif

using stan::prob::_LOG_PROB_;

#include <gtest/gtest.h>
#include <stdexcept>
#include <stan/math/error_handling.hpp>
#include <stan/math/matrix.hpp>

using std::vector;
using Eigen::Matrix;
using Eigen::Dynamic;

using stan::math::default_policy;

typedef boost::math::policies::policy<
  boost::math::policies::domain_error<boost::math::policies::errno_on_error>
  > errno_policy;

class AgradDistributionTest {
public:
  /**
   * Subclasses should define this function.
   *
   */
  virtual void valid_values(vector<vector<double> >& /*parameters*/) {
    throw std::runtime_error("valid_values() not implemented");
  }
  
  // don't need to list nan. checked by the test.
  virtual void invalid_values(vector<size_t>& /*index*/, 
                              vector<double>& /*value*/) {
    throw std::runtime_error("valid_values() not implemented");
  }
};

template<class T>
class AgradDistributionTestFixture : public ::testing::Test {
public:
  vector<double> first_valid_params() {
    vector<vector<double> > params;
    T().valid_values(params); 
    return params[0];
  }
  double e() {
    return 1e-8;
  }
};
template<class T>
class AgradDistributionTestFixture2 : public ::testing::Test {
public:
  vector<double> first_valid_params() {
    vector<vector<double> > params;
    T().valid_values(params); 
    return params[0];
  }
  double e() {
    return 1e-8;
  }
};
template<class T>
class AgradDistributionTestFixture3 : public ::testing::Test {
public:
  vector<double> first_valid_params() {
    vector<vector<double> > params;
    T().valid_values(params); 
    return params[0];
  }
  double e() {
    return 1e-8;
  }
};
template<class T>
class AgradDistributionTestFixture4 : public ::testing::Test {
public:
  vector<double> first_valid_params() {
    vector<vector<double> > params;
    T().valid_values(params); 
    return params[0];
  }
  double e() {
    return 1e-8;
  }
};
template<class T>
class AgradDistributionTestFixture5 : public ::testing::Test {
public:
  vector<double> first_valid_params() {
    vector<vector<double> > params;
    T().valid_values(params); 
    return params[0];
  }
  double e() {
    return 1e-8;
  }
};
template<class T>
class AgradDistributionTestFixture6 : public ::testing::Test {
public:
  vector<double> first_valid_params() {
    vector<vector<double> > params;
    T().valid_values(params); 
    return params[0];
  }
  double e() {
    return 1e-8;
  }
};
template<class T>
class AgradDistributionTestFixture7 : public ::testing::Test {
public:
  vector<double> first_valid_params() {
    vector<vector<double> > params;
    T().valid_values(params); 
    return params[0];
  }
  double e() {
    return 1e-8;
  }
};
TYPED_TEST_CASE_P(AgradDistributionTestFixture);
TYPED_TEST_CASE_P(AgradDistributionTestFixture2);
TYPED_TEST_CASE_P(AgradDistributionTestFixture3);
TYPED_TEST_CASE_P(AgradDistributionTestFixture4);
TYPED_TEST_CASE_P(AgradDistributionTestFixture5);
TYPED_TEST_CASE_P(AgradDistributionTestFixture6);
TYPED_TEST_CASE_P(AgradDistributionTestFixture7);

/**
 * Utility functions
 **/
using stan::agrad::var;
using stan::scalar_type;
using stan::is_vector;
using stan::is_constant;
using stan::is_constant_struct;
namespace std {
  ::std::ostream& operator<<(::std::ostream& os, const vector<double>& param) {
    os << "(";
    for (size_t n = 0; n < param.size(); n++) {
      os << param[n];
      if (n < param.size()-1)
        os << ", ";
    }
    os << ")";
    return os;
  }
}
/** 
 * Gets parameters based on expected type.
 * 
 * @param parameters all parameters
 * @param p column.
 * 
 * @return parameters. If T is double or var, returns a single value, if it is a vector, returns the appropriate vector.
 */
template<class T>
T get_params(vector<vector<double> >& parameters, size_t p) {
  if (p < parameters[0].size())
    return parameters[0][p];
  return 0;
}
template<>
vector<double> get_params<vector<double> >(vector<vector<double> >& parameters, size_t p) {
  vector<double> param(parameters.size());
  for (size_t n = 0; n < parameters.size(); n++)
    if (p < parameters[0].size())
      param[n] = parameters[n][p];
  return param;
}
template<>
vector<var> get_params<vector<var> >(vector<vector<double> >& parameters, size_t p) {
  vector<var> param(parameters.size());
  for (size_t n = 0; n < parameters.size(); n++)
    if (p < parameters[0].size())
      param[n] = parameters[n][p];
  return param;
}
template<>
vector<int> get_params<vector<int> >(vector<vector<double> >& parameters, size_t p) {
  vector<int> param(parameters.size());
  for (size_t n = 0; n < parameters.size(); n++)
    param[n] = parameters[n][p];
  return param;
}

double get_param(vector<double>& param, size_t p) {
  if (p >= param.size())
    return 0;
  return param[p];
}

/** 
 * Gets a single parameter value from the parameter list.
 * Acts like a vector view.
 * 
 * @param parameters parameters
 * @param n row
 * @param p column
 * 
 * @return 
 */
template<class T>
double get_param(vector<vector<double> >& parameters, size_t n, size_t p) {
  if (p >= parameters[0].size())
    return 0;
  if (is_vector<T>::value)    
    return parameters[n][p];
  else
    return parameters[0][p];
}

/** 
 * Add params to the vector of vars.
 * 
 * @param x vector to modify
 * @param p params to add (adds either vector<var> or var, no op for non-auto-diff variables)
 */
template<class T, 
         bool is_const>
void add_params(vector<var>& /*x*/, T* /*p*/) { }

template<>
void add_params<var, false>(vector<var>& x, var* p) {
  x.push_back(*p);
}

template<>
void add_params<vector<var>, false>(vector<var>& x, vector<var>* p) {
  x.insert(x.end(), p->begin(), p->end());
}

/** 
 * Updates expected gradients. Defaults for the template parameters is double,
 * default values for gradient vectors are 0. This will allow matching 
 * calls for a shorter list of template parameters if necessary.
 * 
 * @param logprob 
 * @param grad0 
 * @param p0 
 * @param grad1 
 * @param p1 
 * @param grad2 
 * @param p2 
 * @param grad3 
 * @param p3 
 */
template<class T0, class T1, class T2, class T3,
         class T4, class T5, class T6,
         class T7, class T8, class T9>
void update_expected_gradients(var& logprob,
                               vector<double>* grad0, T0* p0,
                               vector<double>* grad1, T1* p1,
                               vector<double>* grad2, T2* p2, 
                               vector<double>* grad3, T3* p3,
                               vector<double>* grad4, T4* p4, 
                               vector<double>* grad5, T5* p5, 
                               vector<double>* grad6, T6* p6, 
                               vector<double>* grad7, T7* p7, 
                               vector<double>* grad8, T8* p8, 
                               vector<double>* grad9, T9* p9) {
  vector<var> x;
  if (!is_constant<T0>::value)
    x.push_back(*p0);
  if (!is_constant<T1>::value)
    x.push_back(*p1);
  if (!is_constant<T2>::value)
    x.push_back(*p2);
  if (!is_constant<T3>::value)
    x.push_back(*p3);
  if (!is_constant<T4>::value)
    x.push_back(*p4);
  if (!is_constant<T5>::value)
    x.push_back(*p5);
  if (!is_constant<T6>::value)
    x.push_back(*p6);
  if (!is_constant<T7>::value)
    x.push_back(*p7);
  if (!is_constant<T8>::value)
    x.push_back(*p8);
  if (!is_constant<T9>::value)
    x.push_back(*p9);
  vector<double> grad;
  logprob.grad(x, grad);
  if (!is_constant<T0>::value) {
    grad0->push_back(grad[0]);
    grad.erase(grad.begin());
  }
  if (!is_constant<T1>::value) {
    grad1->push_back(grad[0]);
    grad.erase(grad.begin());
  }
  if (!is_constant<T2>::value) {
    grad2->push_back(grad[0]);
    grad.erase(grad.begin());
  }
  if (!is_constant<T3>::value) {
    grad3->push_back(grad[0]);
    grad.erase(grad.begin());
  }
  if (!is_constant<T4>::value) {
    grad4->push_back(grad[0]);
    grad.erase(grad.begin());
  }
  if (!is_constant<T5>::value) {
    grad5->push_back(grad[0]);
    grad.erase(grad.begin());
  }
  if (!is_constant<T6>::value) {
    grad6->push_back(grad[0]);
    grad.erase(grad.begin());
  }
  if (!is_constant<T7>::value) {
    grad7->push_back(grad[0]);
    grad.erase(grad.begin());
  }
  if (!is_constant<T8>::value) {
    grad8->push_back(grad[0]);
    grad.erase(grad.begin());
  }
  if (!is_constant<T9>::value) {
    grad9->push_back(grad[0]);
    grad.erase(grad.begin());
  }
}

/** 
 * Tests a single gradient parameter based on the type provided.
 * 
 * @param e_grad 
 * @param grad 
 * @param p 
 */
template<class T,
         bool is_const>
void test_grad(vector<double>* /*e_grad*/, vector<double>* /*grad*/, size_t /*p*/) { }

template<>
void test_grad<var, false>(vector<double>* e_grad, vector<double>* grad, size_t p) {
  double expected_gradient = stan::math::sum(*e_grad);
  double gradient = (*grad)[0];

  EXPECT_FLOAT_EQ(expected_gradient, gradient)
    << "Gradient test failed for parameter " << p;
  grad->erase(grad->begin());
}
template<>
void test_grad<vector<var>, false>(vector<double>* e_grad, vector<double>* grad, size_t p) {
  for (size_t n = 0; n < e_grad->size(); n++)
    EXPECT_FLOAT_EQ((*e_grad)[n], (*grad)[n])
      << "At index " << n << ". Gradient test failed for parameter " << p;
  grad->erase(grad->begin(), grad->begin() + e_grad->size());
}

template<class T0, class T1, class T2, class T3,
         class T4, class T5, class T6,
         class T7, class T8, class T9>
void test_gradients(var& logprob,
                    vector<double>* e_grad0, T0* p0, 
                    vector<double>* e_grad1, T1* p1,
                    vector<double>* e_grad2, T2* p2, 
                    vector<double>* e_grad3, T3* p3,
                    vector<double>* e_grad4, T4* p4, 
                    vector<double>* e_grad5, T5* p5, 
                    vector<double>* e_grad6, T6* p6, 
                    vector<double>* e_grad7, T7* p7, 
                    vector<double>* e_grad8, T8* p8, 
                    vector<double>* e_grad9, T9* p9) {
  vector<var> x;
  add_params<T0,is_constant_struct<T0>::value>(x, p0);
  add_params<T1,is_constant_struct<T1>::value>(x, p1);
  add_params<T2,is_constant_struct<T2>::value>(x, p2);
  add_params<T3,is_constant_struct<T3>::value>(x, p3);
  add_params<T4,is_constant_struct<T4>::value>(x, p4);
  add_params<T5,is_constant_struct<T5>::value>(x, p5);
  add_params<T6,is_constant_struct<T6>::value>(x, p6);
  add_params<T7,is_constant_struct<T7>::value>(x, p7);
  add_params<T8,is_constant_struct<T8>::value>(x, p8);
  add_params<T9,is_constant_struct<T9>::value>(x, p9);
  
  vector<double> grad;
  logprob.grad(x, grad);
  
  test_grad<T0,is_constant_struct<T0>::value>(e_grad0, &grad, 0);
  test_grad<T1,is_constant_struct<T1>::value>(e_grad1, &grad, 1);
  test_grad<T2,is_constant_struct<T2>::value>(e_grad2, &grad, 2);
  test_grad<T3,is_constant_struct<T3>::value>(e_grad3, &grad, 3);
  test_grad<T4,is_constant_struct<T4>::value>(e_grad4, &grad, 4);
  test_grad<T5,is_constant_struct<T5>::value>(e_grad5, &grad, 5);
  test_grad<T6,is_constant_struct<T6>::value>(e_grad6, &grad, 6);
  test_grad<T7,is_constant_struct<T7>::value>(e_grad7, &grad, 7);
  test_grad<T8,is_constant_struct<T8>::value>(e_grad8, &grad, 8);
  test_grad<T9,is_constant_struct<T9>::value>(e_grad9, &grad, 9);
}

template<class T0, class T1, class T2, class T3,
         class T4, class T5, class T6,
         class T7, class T8, class T9>
class CALL_LOG_PROB;





template<class TypeParam, class T0, 
         class T1=double, class T2=double, class T3=double, 
         class T4=double, class T5=double, class T6=double, 
         class T7=double, class T8=double, class T9=double>
class AgradTest {
public:
  static void test_vectorized() {
    vector<vector<double> > parameters;
    TypeParam().valid_values(parameters);
    ASSERT_GT(parameters.size(), 0U);
    //ASSERT_EQ(parameters[0].size(), 4U);
  
    if (is_constant_struct<T0>::value && is_constant_struct<T1>::value && is_constant_struct<T2>::value && is_constant_struct<T3>::value
        && is_constant_struct<T4>::value && is_constant_struct<T5>::value && is_constant_struct<T6>::value
        && is_constant_struct<T7>::value && is_constant_struct<T8>::value && is_constant_struct<T9>::value) {
      SUCCEED() << "No need to test all double arguments";
      return;
    }
    if (!is_vector<T0>::value && !is_vector<T1>::value && !is_vector<T2>::value && !is_vector<T3>::value
        && !is_vector<T4>::value && !is_vector<T5>::value && !is_vector<T6>::value
        && !is_vector<T7>::value && !is_vector<T8>::value && !is_vector<T9>::value) {
      SUCCEED() << "No need to test all non-vector arguments";
      return;
    }

    double e_logprob(0.0);
    vector<double> e_grad_p0, e_grad_p1, e_grad_p2, e_grad_p3,
      e_grad_p4, e_grad_p5, e_grad_p6,
      e_grad_p7, e_grad_p8, e_grad_p9;
    for (size_t n = 0; n < parameters.size(); n++) {
      typename scalar_type<T0>::type p0 = get_param<T0>(parameters, n, 0);
      typename scalar_type<T1>::type p1 = get_param<T1>(parameters, n, 1);
      typename scalar_type<T2>::type p2 = get_param<T2>(parameters, n, 2);
      typename scalar_type<T3>::type p3 = get_param<T3>(parameters, n, 3);
      typename scalar_type<T4>::type p4 = get_param<T4>(parameters, n, 4);
      typename scalar_type<T5>::type p5 = get_param<T5>(parameters, n, 5);
      typename scalar_type<T6>::type p6 = get_param<T6>(parameters, n, 6);
      typename scalar_type<T7>::type p7 = get_param<T7>(parameters, n, 7);
      typename scalar_type<T8>::type p8 = get_param<T8>(parameters, n, 8);
      typename scalar_type<T9>::type p9 = get_param<T9>(parameters, n, 9);
    
      var logprob = CALL_LOG_PROB<typename scalar_type<T0>::type,
        typename scalar_type<T1>::type,
        typename scalar_type<T2>::type,
        typename scalar_type<T3>::type,
        typename scalar_type<T4>::type,
        typename scalar_type<T5>::type,
        typename scalar_type<T6>::type,
        typename scalar_type<T7>::type,
        typename scalar_type<T8>::type,
        typename scalar_type<T9>::type>()
        .call(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
      e_logprob += logprob.val();
      update_expected_gradients(logprob,
                                &e_grad_p0, &p0,
                                &e_grad_p1, &p1,
                                &e_grad_p2, &p2,
                                &e_grad_p3, &p3,
                                &e_grad_p4, &p4,
                                &e_grad_p5, &p5,
                                &e_grad_p6, &p6,
                                &e_grad_p7, &p7,
                                &e_grad_p8, &p8,
                                &e_grad_p9, &p9);
    }
    T0 p0 = get_params<T0>(parameters, 0);
    T1 p1 = get_params<T1>(parameters, 1);
    T2 p2 = get_params<T2>(parameters, 2);
    T3 p3 = get_params<T3>(parameters, 3);
    T4 p4 = get_params<T4>(parameters, 4);
    T5 p5 = get_params<T5>(parameters, 5);
    T6 p6 = get_params<T6>(parameters, 6);
    T7 p7 = get_params<T7>(parameters, 7);
    T8 p8 = get_params<T8>(parameters, 8);
    T9 p9 = get_params<T9>(parameters, 9);
    var logprob = CALL_LOG_PROB<T0, T1, T2, T3, T4,
      T5, T6, T7, T8, T9>()
      .call(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);

    EXPECT_FLOAT_EQ(e_logprob, logprob.val())
      << "log probability does not match";

    test_gradients(logprob,
                   &e_grad_p0, &p0, 
                   &e_grad_p1, &p1, 
                   &e_grad_p2, &p2, 
                   &e_grad_p3, &p3,
                   &e_grad_p4, &p4, 
                   &e_grad_p5, &p5, 
                   &e_grad_p6, &p6, 
                   &e_grad_p7, &p7, 
                   &e_grad_p8, &p8, 
                   &e_grad_p9, &p9);
    return;
  }


  static void test_valid() {
    vector<vector<double> > parameters;
    TypeParam().valid_values(parameters);
    ASSERT_GT(parameters.size(), 0U);
  
    for (size_t n = 0; n < parameters.size(); n++) {
      vector<double> params = parameters[n];
      T0 p0 = get_params<T0>(parameters, 0);
      T1 p1 = get_params<T1>(parameters, 1);
      T2 p2 = get_params<T2>(parameters, 2);
      T3 p3 = get_params<T3>(parameters, 3);
      T4 p4 = get_params<T4>(parameters, 4);
      T5 p5 = get_params<T5>(parameters, 5);
      T6 p6 = get_params<T6>(parameters, 6);
      T7 p7 = get_params<T7>(parameters, 7);
      T8 p8 = get_params<T8>(parameters, 8);
      T9 p9 = get_params<T9>(parameters, 9);
      var logprob(0);
      EXPECT_NO_THROW( ({
            logprob = CALL_LOG_PROB<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9>()
              .call(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
          }) )
        << "Valid parameters failed at index: " << n << std::endl
        << params;

      if (is_constant_struct<T0>::value && is_constant_struct<T1>::value && is_constant_struct<T2>::value && is_constant_struct<T3>::value
          && is_constant_struct<T4>::value && is_constant_struct<T5>::value && is_constant_struct<T6>::value
          && is_constant_struct<T7>::value && is_constant_struct<T8>::value && is_constant_struct<T9>::value) {
        EXPECT_FLOAT_EQ(0.0, logprob.val())
          << "Valid parameters, failed propto calculation with all doubles at index: " << n << std::endl
          << params;

      }
    }  
  }

  static void test_invalid() {
    if (is_vector<T0>::value || is_vector<T1>::value || is_vector<T2>::value || is_vector<T3>::value
        || is_vector<T4>::value || is_vector<T5>::value || is_vector<T6>::value
        || is_vector<T7>::value || is_vector<T8>::value || is_vector<T9>::value) {
      SUCCEED() << "No need to test non-vector arguments";
      return;
    }

    vector<vector<double> > parameters;
    TypeParam().valid_values(parameters);
    CALL_LOG_PROB<typename scalar_type<T0>::type,
      typename scalar_type<T1>::type,
      typename scalar_type<T2>::type,
      typename scalar_type<T3>::type,
      typename scalar_type<T4>::type,
      typename scalar_type<T5>::type,
      typename scalar_type<T6>::type,
      typename scalar_type<T7>::type,
      typename scalar_type<T8>::type,
      typename scalar_type<T9>::type>
      call_log_prob;
    

    vector<size_t> index;
    vector<double> invalid_values;
  
    TypeParam().invalid_values(index, invalid_values);
    ASSERT_EQ(index.size(), invalid_values.size());

    for (size_t n = 0; n < index.size(); n++) {
      vector<double> invalid_params(parameters[0]);
      invalid_params[index[n]] = invalid_values[n];
    
      typename scalar_type<T0>::type p0 = get_param(invalid_params, 0);
      typename scalar_type<T1>::type p1 = get_param(invalid_params, 1);
      typename scalar_type<T2>::type p2 = get_param(invalid_params, 2);
      typename scalar_type<T3>::type p3 = get_param(invalid_params, 3);
      typename scalar_type<T4>::type p4 = get_param(invalid_params, 4);
      typename scalar_type<T5>::type p5 = get_param(invalid_params, 5);
      typename scalar_type<T6>::type p6 = get_param(invalid_params, 6);
      typename scalar_type<T7>::type p7 = get_param(invalid_params, 7);
      typename scalar_type<T8>::type p8 = get_param(invalid_params, 8);
      typename scalar_type<T9>::type p9 = get_param(invalid_params, 9);

      EXPECT_THROW( ({
            call_log_prob.call(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
          }),
        std::domain_error)
        << "Default policy failed at index: " << n << std::endl
        << invalid_params;
    }
    if (std::numeric_limits<T0>::has_quiet_NaN && parameters[0].size() > 0) {
      vector<double> invalid_params(parameters[0]);
      invalid_params[0] = std::numeric_limits<double>::quiet_NaN();
    
      typename scalar_type<T0>::type p0 = get_param(invalid_params, 0);
      typename scalar_type<T1>::type p1 = get_param(invalid_params, 1);
      typename scalar_type<T2>::type p2 = get_param(invalid_params, 2);
      typename scalar_type<T3>::type p3 = get_param(invalid_params, 3);
      typename scalar_type<T4>::type p4 = get_param(invalid_params, 4);
      typename scalar_type<T5>::type p5 = get_param(invalid_params, 5);
      typename scalar_type<T6>::type p6 = get_param(invalid_params, 6);
      typename scalar_type<T7>::type p7 = get_param(invalid_params, 7);
      typename scalar_type<T8>::type p8 = get_param(invalid_params, 8);
      typename scalar_type<T9>::type p9 = get_param(invalid_params, 9);    
      EXPECT_THROW( ({
            call_log_prob.call(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
          }),
        std::domain_error)
        << "Default policy with NaN for parameter: " << 0 << std::endl
        << invalid_params;
    }
    if (std::numeric_limits<T1>::has_quiet_NaN && parameters[0].size() > 1) {
      vector<double> invalid_params(parameters[0]);
      invalid_params[1] = std::numeric_limits<double>::quiet_NaN();
    
      typename scalar_type<T0>::type p0 = get_param(invalid_params, 0);
      typename scalar_type<T1>::type p1 = get_param(invalid_params, 1);
      typename scalar_type<T2>::type p2 = get_param(invalid_params, 2);
      typename scalar_type<T3>::type p3 = get_param(invalid_params, 3);
      typename scalar_type<T4>::type p4 = get_param(invalid_params, 4);
      typename scalar_type<T5>::type p5 = get_param(invalid_params, 5);
      typename scalar_type<T6>::type p6 = get_param(invalid_params, 6);
      typename scalar_type<T7>::type p7 = get_param(invalid_params, 7);
      typename scalar_type<T8>::type p8 = get_param(invalid_params, 8);
      typename scalar_type<T9>::type p9 = get_param(invalid_params, 9);
      EXPECT_THROW( ({
            call_log_prob.call(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
          }),
        std::domain_error)
        << "Default policy with NaN for parameter: " << 1 << std::endl
        << invalid_params;
    }
    if (std::numeric_limits<T2>::has_quiet_NaN && parameters[0].size() > 2) {
      vector<double> invalid_params(parameters[0]);
      invalid_params[2] = std::numeric_limits<double>::quiet_NaN();
    
      typename scalar_type<T0>::type p0 = get_param(invalid_params, 0);
      typename scalar_type<T1>::type p1 = get_param(invalid_params, 1);
      typename scalar_type<T2>::type p2 = get_param(invalid_params, 2);
      typename scalar_type<T3>::type p3 = get_param(invalid_params, 3);
      typename scalar_type<T4>::type p4 = get_param(invalid_params, 4);
      typename scalar_type<T5>::type p5 = get_param(invalid_params, 5);
      typename scalar_type<T6>::type p6 = get_param(invalid_params, 6);
      typename scalar_type<T7>::type p7 = get_param(invalid_params, 7);
      typename scalar_type<T8>::type p8 = get_param(invalid_params, 8);
      typename scalar_type<T9>::type p9 = get_param(invalid_params, 9);    
      EXPECT_THROW( ({
            call_log_prob.call(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
          }),
        std::domain_error)
        << "Default policy with NaN for parameter: " << 2 << std::endl
        << invalid_params;
    }
    if (std::numeric_limits<T3>::has_quiet_NaN && parameters[0].size() > 3) {
      vector<double> invalid_params(parameters[0]);
      invalid_params[3] = std::numeric_limits<double>::quiet_NaN();
    
      typename scalar_type<T0>::type p0 = get_param(invalid_params, 0);
      typename scalar_type<T1>::type p1 = get_param(invalid_params, 1);
      typename scalar_type<T2>::type p2 = get_param(invalid_params, 2);
      typename scalar_type<T3>::type p3 = get_param(invalid_params, 3);
      typename scalar_type<T4>::type p4 = get_param(invalid_params, 4);
      typename scalar_type<T5>::type p5 = get_param(invalid_params, 5);
      typename scalar_type<T6>::type p6 = get_param(invalid_params, 6);
      typename scalar_type<T7>::type p7 = get_param(invalid_params, 7);
      typename scalar_type<T8>::type p8 = get_param(invalid_params, 8);
      typename scalar_type<T9>::type p9 = get_param(invalid_params, 9);    
      EXPECT_THROW( ({
            call_log_prob.call(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
          }),
        std::domain_error)
        << "Default policy with NaN for parameter: " << 3 << std::endl
        << invalid_params;
    }
    if (std::numeric_limits<T4>::has_quiet_NaN && parameters[0].size() > 4) {
      vector<double> invalid_params(parameters[0]);
      invalid_params[4] = std::numeric_limits<double>::quiet_NaN();
    
      typename scalar_type<T0>::type p0 = get_param(invalid_params, 0);
      typename scalar_type<T1>::type p1 = get_param(invalid_params, 1);
      typename scalar_type<T2>::type p2 = get_param(invalid_params, 2);
      typename scalar_type<T3>::type p3 = get_param(invalid_params, 3);
      typename scalar_type<T4>::type p4 = get_param(invalid_params, 4);
      typename scalar_type<T5>::type p5 = get_param(invalid_params, 5);
      typename scalar_type<T6>::type p6 = get_param(invalid_params, 6);
      typename scalar_type<T7>::type p7 = get_param(invalid_params, 7);
      typename scalar_type<T8>::type p8 = get_param(invalid_params, 8);
      typename scalar_type<T9>::type p9 = get_param(invalid_params, 9);
      EXPECT_THROW( ({
            call_log_prob.call(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
          }),
        std::domain_error)
        << "Default policy with NaN for parameter: " << 4 << std::endl
        << invalid_params;
    }
    if (std::numeric_limits<T5>::has_quiet_NaN && parameters[0].size() > 5) {
      vector<double> invalid_params(parameters[0]);
      invalid_params[5] = std::numeric_limits<double>::quiet_NaN();
    
      typename scalar_type<T0>::type p0 = get_param(invalid_params, 0);
      typename scalar_type<T1>::type p1 = get_param(invalid_params, 1);
      typename scalar_type<T2>::type p2 = get_param(invalid_params, 2);
      typename scalar_type<T3>::type p3 = get_param(invalid_params, 3);
      typename scalar_type<T4>::type p4 = get_param(invalid_params, 4);
      typename scalar_type<T5>::type p5 = get_param(invalid_params, 5);
      typename scalar_type<T6>::type p6 = get_param(invalid_params, 6);
      typename scalar_type<T7>::type p7 = get_param(invalid_params, 7);
      typename scalar_type<T8>::type p8 = get_param(invalid_params, 8);
      typename scalar_type<T9>::type p9 = get_param(invalid_params, 9);    
      EXPECT_THROW( ({
            call_log_prob.call(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
          }),
        std::domain_error)
        << "Default policy with NaN for parameter: " << 5 << std::endl
        << invalid_params;
    }
    if (std::numeric_limits<T6>::has_quiet_NaN && parameters[0].size() > 6) {
      vector<double> invalid_params(parameters[0]);
      invalid_params[6] = std::numeric_limits<double>::quiet_NaN();
    
      typename scalar_type<T0>::type p0 = get_param(invalid_params, 0);
      typename scalar_type<T1>::type p1 = get_param(invalid_params, 1);
      typename scalar_type<T2>::type p2 = get_param(invalid_params, 2);
      typename scalar_type<T3>::type p3 = get_param(invalid_params, 3);
      typename scalar_type<T4>::type p4 = get_param(invalid_params, 4);
      typename scalar_type<T5>::type p5 = get_param(invalid_params, 5);
      typename scalar_type<T6>::type p6 = get_param(invalid_params, 6);
      typename scalar_type<T7>::type p7 = get_param(invalid_params, 7);
      typename scalar_type<T8>::type p8 = get_param(invalid_params, 8);
      typename scalar_type<T9>::type p9 = get_param(invalid_params, 9);    
      EXPECT_THROW( ({
            call_log_prob.call(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
          }),
        std::domain_error)
        << "Default policy with NaN for parameter: " << 6 << std::endl
        << invalid_params;
    }
    if (std::numeric_limits<T7>::has_quiet_NaN && parameters[0].size() > 7) {
      vector<double> invalid_params(parameters[0]);
      invalid_params[7] = std::numeric_limits<double>::quiet_NaN();
    
      typename scalar_type<T0>::type p0 = get_param(invalid_params, 0);
      typename scalar_type<T1>::type p1 = get_param(invalid_params, 1);
      typename scalar_type<T2>::type p2 = get_param(invalid_params, 2);
      typename scalar_type<T3>::type p3 = get_param(invalid_params, 3);
      typename scalar_type<T4>::type p4 = get_param(invalid_params, 4);
      typename scalar_type<T5>::type p5 = get_param(invalid_params, 5);
      typename scalar_type<T6>::type p6 = get_param(invalid_params, 6);
      typename scalar_type<T7>::type p7 = get_param(invalid_params, 7);
      typename scalar_type<T8>::type p8 = get_param(invalid_params, 8);
      typename scalar_type<T9>::type p9 = get_param(invalid_params, 9);    
      EXPECT_THROW( ({
            call_log_prob.call(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
          }),
        std::domain_error)
        << "Default policy with NaN for parameter: " << 7 << std::endl
        << invalid_params;
    }
    if (std::numeric_limits<T8>::has_quiet_NaN && parameters[0].size() > 8) {
      vector<double> invalid_params(parameters[0]);
      invalid_params[8] = std::numeric_limits<double>::quiet_NaN();
    
      typename scalar_type<T0>::type p0 = get_param(invalid_params, 0);
      typename scalar_type<T1>::type p1 = get_param(invalid_params, 1);
      typename scalar_type<T2>::type p2 = get_param(invalid_params, 2);
      typename scalar_type<T3>::type p3 = get_param(invalid_params, 3);
      typename scalar_type<T4>::type p4 = get_param(invalid_params, 4);
      typename scalar_type<T5>::type p5 = get_param(invalid_params, 5);
      typename scalar_type<T6>::type p6 = get_param(invalid_params, 6);
      typename scalar_type<T7>::type p7 = get_param(invalid_params, 7);
      typename scalar_type<T8>::type p8 = get_param(invalid_params, 8);
      typename scalar_type<T9>::type p9 = get_param(invalid_params, 9);   
      EXPECT_THROW( ({
            call_log_prob.call(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
          }),
        std::domain_error)
        << "Default policy with NaN for parameter: " << 8 << std::endl
        << invalid_params;
    }
    if (std::numeric_limits<T9>::has_quiet_NaN && parameters[0].size() > 9) {
      vector<double> invalid_params(parameters[0]);
      invalid_params[9] = std::numeric_limits<double>::quiet_NaN();

      typename scalar_type<T0>::type p0 = get_param(invalid_params, 0);
      typename scalar_type<T1>::type p1 = get_param(invalid_params, 1);
      typename scalar_type<T2>::type p2 = get_param(invalid_params, 2);
      typename scalar_type<T3>::type p3 = get_param(invalid_params, 3);
      typename scalar_type<T4>::type p4 = get_param(invalid_params, 4);
      typename scalar_type<T5>::type p5 = get_param(invalid_params, 5);
      typename scalar_type<T6>::type p6 = get_param(invalid_params, 6);
      typename scalar_type<T7>::type p7 = get_param(invalid_params, 7);
      typename scalar_type<T8>::type p8 = get_param(invalid_params, 8);
      typename scalar_type<T9>::type p9 = get_param(invalid_params, 9);
      EXPECT_THROW( ({
            call_log_prob.call(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
          }),
        std::domain_error)
        << "Default policy with NaN for parameter: " << 9 << std::endl
        << invalid_params;
    }
  }

  static void test_propto() {
    if (is_constant_struct<T0>::value && is_constant_struct<T1>::value && is_constant_struct<T2>::value && is_constant_struct<T3>::value
        && is_constant_struct<T4>::value && is_constant_struct<T5>::value && is_constant_struct<T6>::value
        && is_constant_struct<T7>::value && is_constant_struct<T8>::value && is_constant_struct<T9>::value) {
      SUCCEED() << "No need to test all double arguments";
      return;
    }
    if (is_vector<T0>::value || is_vector<T1>::value || is_vector<T2>::value || is_vector<T3>::value
        || is_vector<T4>::value || is_vector<T5>::value || is_vector<T6>::value
        || is_vector<T7>::value || is_vector<T8>::value || is_vector<T9>::value) {
      SUCCEED() << "No need to test non-vector arguments";
      return;
    }

    CALL_LOG_PROB<typename scalar_type<T0>::type,
        typename scalar_type<T1>::type,
        typename scalar_type<T2>::type,
        typename scalar_type<T3>::type,
        typename scalar_type<T4>::type,
        typename scalar_type<T5>::type,
        typename scalar_type<T6>::type,
        typename scalar_type<T7>::type,
        typename scalar_type<T8>::type,
        typename scalar_type<T9>::type>
      call_log_prob;
  
    vector<vector<double> > parameters;
    TypeParam().valid_values(parameters);
    vector<double> reference_params = parameters[0];
    var reference_logprob_true;
    var reference_logprob_false;
    {
      typename scalar_type<T0>::type p0 = get_param(reference_params, 0);
      typename scalar_type<T1>::type p1 = get_param(reference_params, 1);
      typename scalar_type<T2>::type p2 = get_param(reference_params, 2);
      typename scalar_type<T3>::type p3 = get_param(reference_params, 3);
      typename scalar_type<T4>::type p4 = get_param(reference_params, 4);
      typename scalar_type<T5>::type p5 = get_param(reference_params, 5);
      typename scalar_type<T6>::type p6 = get_param(reference_params, 6);
      typename scalar_type<T7>::type p7 = get_param(reference_params, 7);
      typename scalar_type<T8>::type p8 = get_param(reference_params, 8);
      typename scalar_type<T9>::type p9 = get_param(reference_params, 9);
      reference_logprob_true = call_log_prob.call(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
      reference_logprob_false = call_log_prob.call_nopropto(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
    }

    for (size_t n = 0; n < parameters.size(); n++) {
      vector<double> params(parameters[n]);

      typename scalar_type<T0>::type p0 = get_param<T0>(parameters, n, 0);
      typename scalar_type<T1>::type p1 = get_param<T1>(parameters, n, 1);
      typename scalar_type<T2>::type p2 = get_param<T2>(parameters, n, 2);
      typename scalar_type<T3>::type p3 = get_param<T3>(parameters, n, 3);
      typename scalar_type<T4>::type p4 = get_param<T4>(parameters, n, 4);
      typename scalar_type<T5>::type p5 = get_param<T5>(parameters, n, 5);
      typename scalar_type<T6>::type p6 = get_param<T6>(parameters, n, 6);
      typename scalar_type<T7>::type p7 = get_param<T7>(parameters, n, 7);
      typename scalar_type<T8>::type p8 = get_param<T8>(parameters, n, 8);
      typename scalar_type<T9>::type p9 = get_param<T9>(parameters, n, 9);


      var logprob_true = call_log_prob.call(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
      var logprob_false = call_log_prob.call_nopropto(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
    
      EXPECT_FLOAT_EQ(reference_logprob_false.val() - logprob_false.val(),
                      reference_logprob_true.val() - logprob_true.val())
        << "Propto failed at index: " << n << std::endl
        << "_LOG_PROB_<true>" << params << " = " << logprob_true << std::endl
        << "_LOG_PROB_<true>" << reference_params << " = " << reference_logprob_true << std::endl
        << "_LOG_PROB_<false>" << params << " = " << logprob_false << std::endl
        << "_LOG_PROB_<false>" << reference_params << " = " << reference_logprob_false << std::endl;
    }
  }
  
  static void test_finite_diff() {
    if (is_constant_struct<T0>::value && is_constant_struct<T1>::value && is_constant_struct<T2>::value && is_constant_struct<T3>::value
        && is_constant_struct<T4>::value && is_constant_struct<T5>::value && is_constant_struct<T6>::value
        && is_constant_struct<T7>::value && is_constant_struct<T8>::value && is_constant_struct<T9>::value) {
      SUCCEED() << "No need to test all double arguments";
      return;
    }
    if (is_vector<T0>::value || is_vector<T1>::value || is_vector<T2>::value || is_vector<T3>::value
        || is_vector<T4>::value || is_vector<T5>::value || is_vector<T6>::value
        || is_vector<T7>::value || is_vector<T8>::value || is_vector<T9>::value) {
      SUCCEED() << "No need to test non-vector arguments";
      return;
    }
    using stan::math::value_of;
    
    vector<vector<double> > parameters;
    TypeParam().valid_values(parameters);
  
    CALL_LOG_PROB<typename scalar_type<T0>::type,
        typename scalar_type<T1>::type,
        typename scalar_type<T2>::type,
        typename scalar_type<T3>::type,
        typename scalar_type<T4>::type,
        typename scalar_type<T5>::type,
        typename scalar_type<T6>::type,
        typename scalar_type<T7>::type,
        typename scalar_type<T8>::type,
        typename scalar_type<T9>::type>
      call_log_prob;
    CALL_LOG_PROB<double,double,double,double,double,
      double,double,double,double,typename is_vector<T9>::type>
      call_double_log_prob;
    const double e = 1e-8;
    const double e2 = 2 * e;
    const double tolerance = 1e-4;
    for (size_t n = 0; n < parameters.size(); n++) {
      vector<double> params(parameters[n]);
      vector<double> grad;
      {
	typename scalar_type<T0>::type p0 = get_param(params, 0);
	typename scalar_type<T1>::type p1 = get_param(params, 1);
	typename scalar_type<T2>::type p2 = get_param(params, 2);
	typename scalar_type<T3>::type p3 = get_param(params, 3);
	typename scalar_type<T4>::type p4 = get_param(params, 4);
	typename scalar_type<T5>::type p5 = get_param(params, 5);
	typename scalar_type<T6>::type p6 = get_param(params, 6);
	typename scalar_type<T7>::type p7 = get_param(params, 7);
	typename scalar_type<T8>::type p8 = get_param(params, 8);
	typename scalar_type<T9>::type p9 = get_param(params, 9);
        var logprob = call_log_prob.call_nopropto(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
        vector<var> x;
        if (!is_constant<T0>::value)
          x.push_back(p0);
        if (!is_constant<T1>::value)
          x.push_back(p1);
        if (!is_constant<T2>::value)
          x.push_back(p2);
        if (!is_constant<T3>::value)
          x.push_back(p3);
        if (!is_constant<T4>::value)
          x.push_back(p4);
        if (!is_constant<T5>::value)
          x.push_back(p5);
        if (!is_constant<T6>::value)
          x.push_back(p6);
        if (!is_constant<T7>::value)
          x.push_back(p7);
        if (!is_constant<T8>::value)
          x.push_back(p8);
        if (!is_constant<T9>::value)
          x.push_back(p9);
        logprob.grad(x, grad);
      }
      double p0 = get_param(params, 0);
      double p1 = get_param(params, 1);
      double p2 = get_param(params, 2);
      double p3 = get_param(params, 3);
      double p4 = get_param(params, 4);
      double p5 = get_param(params, 5);
      double p6 = get_param(params, 6);
      double p7 = get_param(params, 7);
      double p8 = get_param(params, 8);
      double p9 = get_param(params, 9);
      if (!is_constant<T0>::value) {
        double plus = p0 + e;
        double minus = p0 - e;
        double grad_finite_diff 
          = (value_of(call_double_log_prob.call_nopropto(plus, p1, p2, p3, p4, p5, p6, p7, p8, p9))
             - value_of(call_double_log_prob.call_nopropto(minus, p1, p2, p3, p4, p5, p6, p7, p8, p9))) / e2;
        EXPECT_NEAR(grad_finite_diff,grad[0],tolerance)
          << "Finite diff test failed for parameter 0" << std::endl << params;
        grad.erase(grad.begin());
      }
      if (!is_constant<T1>::value) {
        double plus = p1 + e;
        double minus = p1 - e;
        double grad_finite_diff 
          = (value_of(call_double_log_prob.call_nopropto(p0, plus, p2, p3, p4, p5, p6, p7, p8, p9))
             - value_of(call_double_log_prob.call_nopropto(p0, minus, p2, p3, p4, p5, p6, p7, p8, p9))) / e2;
        EXPECT_NEAR(grad_finite_diff,grad[0],tolerance)
          << "Finite diff test failed for parameter 1" << std::endl << params;
        grad.erase(grad.begin());
      }
      if (!is_constant<T2>::value) {
        double plus = p2 + e;
        double minus = p2 - e;
        double grad_finite_diff 
          = (value_of(call_double_log_prob.call_nopropto(p0, p1, plus, p3, p4, p5, p6, p7, p8, p9))
             - value_of(call_double_log_prob.call_nopropto(p0, p1, minus, p3, p4, p5, p6, p7, p8, p9))) / e2;
        EXPECT_NEAR(grad_finite_diff,grad[0],tolerance)
          << "Finite diff test failed for parameter 2" << std::endl << params;
        grad.erase(grad.begin());
      }
      if (!is_constant<T3>::value) {
        double plus = p3 + e;
        double minus = p3 - e;
        double grad_finite_diff 
          = (value_of(call_double_log_prob.call_nopropto(p0, p1, p2, plus, p4, p5, p6, p7, p8, p9))
             - value_of(call_double_log_prob.call_nopropto(p0, p1, p2, minus, p4, p5, p6, p7, p8, p9))) / e2;
        EXPECT_NEAR(grad_finite_diff,grad[0],tolerance)
          << "Finite diff test failed for parameter 3" << std::endl << params;
        grad.erase(grad.begin());
      }
      if (!is_constant<T4>::value) {
        double plus = p4 + e;
        double minus = p4 - e;
        double grad_finite_diff 
          = (value_of(call_double_log_prob.call_nopropto(p0, p1, p2, p3, plus, p5, p6, p7, p8, p9))
             - value_of(call_double_log_prob.call_nopropto(p0, p1, p2, p3, minus, p5, p6, p7, p8, p9))) / e2;
        EXPECT_NEAR(grad_finite_diff,grad[0],tolerance)
          << "Finite diff test failed for parameter 4" << std::endl << params;
        grad.erase(grad.begin());
      }
      if (!is_constant<T5>::value) {
        double plus = p5 + e;
        double minus = p5 - e;
        double grad_finite_diff 
          = (value_of(call_double_log_prob.call_nopropto(p0, p1, p2, p3, p4, plus, p6, p7, p8, p9))
             - value_of(call_double_log_prob.call_nopropto(p0, p1, p2, p3, p4, minus, p6, p7, p8, p9))) / e2;
        EXPECT_NEAR(grad_finite_diff,grad[0],tolerance)
          << "Finite diff test failed for parameter 5" << std::endl << params;
        grad.erase(grad.begin());
      }
      if (!is_constant<T6>::value) {
        double plus = p6 + e;
        double minus = p6 - e;
        double grad_finite_diff 
          = (value_of(call_double_log_prob.call_nopropto(p0, p1, p2, p3, p4, p5, plus, p7, p8, p9))
             - value_of(call_double_log_prob.call_nopropto(p0, p1, p2, p3, p4, p5, minus, p7, p8, p9))) / e2;
        EXPECT_NEAR(grad_finite_diff,grad[0],tolerance)
          << "Finite diff test failed for parameter 6" << std::endl << params;
        grad.erase(grad.begin());
      }
      if (!is_constant<T7>::value) {
        double plus = p7 + e;
        double minus = p7 - e;
        double grad_finite_diff 
          = (value_of(call_double_log_prob.call_nopropto(p0, p1, p2, p3, p4, p5, p6, plus, p8, p9))
             - value_of(call_double_log_prob.call_nopropto(p0, p1, p2, p3, p4, p5, p6, minus, p8, p9))) / e2;
        EXPECT_NEAR(grad_finite_diff,grad[0],tolerance)
          << "Finite diff test failed for parameter 7" << std::endl << params;
        grad.erase(grad.begin());
      }
      if (!is_constant<T8>::value) {
        double plus = p8 + e;
        double minus = p8 - e;
        double grad_finite_diff 
          = (value_of(call_double_log_prob.call_nopropto(p0, p1, p2, p3, p4, p5, p6, p7, plus, p9))
             - value_of(call_double_log_prob.call_nopropto(p0, p1, p2, p3, p4, p5, p6, p7, minus, p9))) / e2;
        EXPECT_NEAR(grad_finite_diff,grad[0],tolerance)
          << "Finite diff test failed for parameter 8" << std::endl << params;
        grad.erase(grad.begin());
      }
      if (!is_constant<T9>::value) {
        double plus = p9 + e;
        double minus = p9 - e;
        double grad_finite_diff 
          = (value_of(call_double_log_prob.call_nopropto(p0, p1, p2, p3, p4, p5, p6, p7, p8, plus))
             - value_of(call_double_log_prob.call_nopropto(p0, p1, p2, p3, p4, p5, p6, p7, p8, minus))) / e2;
        EXPECT_NEAR(grad_finite_diff,grad[0],tolerance)
          << "Finite diff test failed for parameter 9" << std::endl << params;
        grad.erase(grad.begin());    
      }
      ASSERT_EQ(0U, grad.size()) 
        << "Something is wrong with the test. We should have compared all gradients.";    
    }
  }

  static void test_gradient_function() {
    using stan::math::value_of;
    if (is_constant_struct<T0>::value && is_constant_struct<T1>::value && is_constant_struct<T2>::value && is_constant_struct<T3>::value
        && is_constant_struct<T4>::value && is_constant_struct<T5>::value && is_constant_struct<T6>::value
        && is_constant_struct<T7>::value && is_constant_struct<T8>::value && is_constant_struct<T9>::value) {
      SUCCEED() << "No need to test all double arguments";
      return;
    }
    if (is_vector<T0>::value || is_vector<T1>::value || is_vector<T2>::value || is_vector<T3>::value
        || is_vector<T4>::value || is_vector<T5>::value || is_vector<T6>::value
        || is_vector<T7>::value || is_vector<T8>::value || is_vector<T9>::value) {
      SUCCEED() << "No need to test non-vector arguments";
      return;
    }
    vector<vector<double> > parameters;
    TypeParam().valid_values(parameters);
  
    CALL_LOG_PROB<typename scalar_type<T0>::type,
      typename scalar_type<T1>::type,
      typename scalar_type<T2>::type,
      typename scalar_type<T3>::type,
      typename scalar_type<T4>::type,
      typename scalar_type<T5>::type,
      typename scalar_type<T6>::type,
      typename scalar_type<T7>::type,
      typename scalar_type<T8>::type,
      typename scalar_type<T9>::type> call_log_prob;

    for (size_t n = 0; n < parameters.size(); n++) {
      vector<double> params(parameters[n]);
      vector<double> expected_grad;
      vector<double> grad;
      {
	typename scalar_type<T0>::type p0 = get_param(params, 0);
	typename scalar_type<T1>::type p1 = get_param(params, 1);
	typename scalar_type<T2>::type p2 = get_param(params, 2);
	typename scalar_type<T3>::type p3 = get_param(params, 3);
	typename scalar_type<T4>::type p4 = get_param(params, 4);
	typename scalar_type<T5>::type p5 = get_param(params, 5);
	typename scalar_type<T6>::type p6 = get_param(params, 6);
	typename scalar_type<T7>::type p7 = get_param(params, 7);
	typename scalar_type<T8>::type p8 = get_param(params, 8);
	typename scalar_type<T9>::type p9 = get_param(params, 9);
        var logprob = TypeParam().log_prob(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
        vector<var> x;
        if (!is_constant<T0>::value)
          x.push_back(p0);
        if (!is_constant<T1>::value)
          x.push_back(p1);
        if (!is_constant<T2>::value)
          x.push_back(p2);
        if (!is_constant<T3>::value)
          x.push_back(p3);
        if (!is_constant<T4>::value)
          x.push_back(p4);
        if (!is_constant<T5>::value)
          x.push_back(p5);
        if (!is_constant<T6>::value)
          x.push_back(p6);
        if (!is_constant<T7>::value)
          x.push_back(p7);
        if (!is_constant<T8>::value)
          x.push_back(p8);
        if (!is_constant<T9>::value)
          x.push_back(p9);
        logprob.grad(x, expected_grad);
      }
      {
	typename scalar_type<T0>::type p0 = get_param(params, 0);
	typename scalar_type<T1>::type p1 = get_param(params, 1);
	typename scalar_type<T2>::type p2 = get_param(params, 2);
	typename scalar_type<T3>::type p3 = get_param(params, 3);
	typename scalar_type<T4>::type p4 = get_param(params, 4);
	typename scalar_type<T5>::type p5 = get_param(params, 5);
	typename scalar_type<T6>::type p6 = get_param(params, 6);
	typename scalar_type<T7>::type p7 = get_param(params, 7);
	typename scalar_type<T8>::type p8 = get_param(params, 8);
	typename scalar_type<T9>::type p9 = get_param(params, 9);
        var logprob = call_log_prob.call_nopropto(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
        vector<var> x;
        if (!is_constant<T0>::value)
          x.push_back(p0);
        if (!is_constant<T1>::value)
          x.push_back(p1);
        if (!is_constant<T2>::value)
          x.push_back(p2);
        if (!is_constant<T3>::value)
          x.push_back(p3);
        if (!is_constant<T4>::value)
          x.push_back(p4);
        if (!is_constant<T5>::value)
          x.push_back(p5);
        if (!is_constant<T6>::value)
          x.push_back(p6);
        if (!is_constant<T7>::value)
          x.push_back(p7);
        if (!is_constant<T8>::value)
          x.push_back(p8);
        if (!is_constant<T9>::value)
          x.push_back(p9);
        logprob.grad(x, grad);
      }
      ASSERT_EQ(expected_grad.size(), grad.size())
        << "Something is wrong with the log_prob() defined in the test";
      if (!is_constant<T0>::value) {
        EXPECT_FLOAT_EQ(expected_grad[0],grad[0])
          << "Hand coded gradient failed for param 0" << std::endl << params;
        grad.erase(grad.begin());
        expected_grad.erase(expected_grad.begin());
      }
      if (!is_constant<T1>::value) {
        EXPECT_FLOAT_EQ(expected_grad[0],grad[0])
          << "Hand coded gradient failed for param 1" << std::endl << params;
        grad.erase(grad.begin());
        expected_grad.erase(expected_grad.begin());
      }  
      if (!is_constant<T2>::value) {
        EXPECT_FLOAT_EQ(expected_grad[0],grad[0])
          << "Hand coded gradient failed for param 2" << std::endl << params;
        grad.erase(grad.begin());
        expected_grad.erase(expected_grad.begin());
      }
      if (!is_constant<T3>::value) {
        EXPECT_FLOAT_EQ(expected_grad[0],grad[0])
          << "Hand coded gradient failed for param 3" << std::endl << params;
        grad.erase(grad.begin());
        expected_grad.erase(expected_grad.begin());
      }
      if (!is_constant<T4>::value) {
        EXPECT_FLOAT_EQ(expected_grad[0],grad[0])
          << "Hand coded gradient failed for param 4" << std::endl << params;
        grad.erase(grad.begin());
        expected_grad.erase(expected_grad.begin());
      }
      if (!is_constant<T5>::value) {
        EXPECT_FLOAT_EQ(expected_grad[0],grad[0])
          << "Hand coded gradient failed for param 5" << std::endl << params;
        grad.erase(grad.begin());
        expected_grad.erase(expected_grad.begin());
      }
      if (!is_constant<T6>::value) {
        EXPECT_FLOAT_EQ(expected_grad[0],grad[0])
          << "Hand coded gradient failed for param 6" << std::endl << params;
        grad.erase(grad.begin());
        expected_grad.erase(expected_grad.begin());
      }
      if (!is_constant<T7>::value) {
        EXPECT_FLOAT_EQ(expected_grad[0],grad[0])
          << "Hand coded gradient failed for param 7" << std::endl << params;
        grad.erase(grad.begin());
        expected_grad.erase(expected_grad.begin());
      }
      if (!is_constant<T8>::value) {
        EXPECT_FLOAT_EQ(expected_grad[0],grad[0])
          << "Hand coded gradient failed for param 8" << std::endl << params;
        grad.erase(grad.begin());
        expected_grad.erase(expected_grad.begin());
      }
      if (!is_constant<T9>::value) {
        EXPECT_FLOAT_EQ(expected_grad[0],grad[0])
          << "Hand coded gradient failed for param 9" << std::endl << params;
        grad.erase(grad.begin());
        expected_grad.erase(expected_grad.begin());
      }
    }
  
  }
};
#endif
