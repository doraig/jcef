// Copyright (c) 2014 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "CefRequest_N.h"
#include "include/cef_request.h"
#include "jni_util.h"
#include "util.h"

JNIEXPORT void JNICALL
Java_org_cef_network_CefRequest_1N_N_1CefRequest_1CTOR(JNIEnv* env,
                                                       jobject obj) {
  CefRefPtr<CefRequest> request = CefRequest::Create();
  if (!request.get())
    return;
  SetCefForJNIObject(env, obj, request.get(), "CefRequest");
}

JNIEXPORT jlong JNICALL
Java_org_cef_network_CefRequest_1N_N_1GetIdentifier(JNIEnv* env, jobject obj) {
  CefRefPtr<CefRequest> request =
      GetCefFromJNIObject<CefRequest>(env, obj, "CefRequest");
  if (!request)
    return 0;
  return (jlong)request->GetIdentifier();
}

JNIEXPORT jboolean JNICALL
Java_org_cef_network_CefRequest_1N_N_1IsReadOnly(JNIEnv* env, jobject obj) {
  CefRefPtr<CefRequest> request =
      GetCefFromJNIObject<CefRequest>(env, obj, "CefRequest");
  if (!request)
    return JNI_FALSE;
  return request->IsReadOnly() ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jstring JNICALL
Java_org_cef_network_CefRequest_1N_N_1GetURL(JNIEnv* env, jobject obj) {
  CefRefPtr<CefRequest> request =
      GetCefFromJNIObject<CefRequest>(env, obj, "CefRequest");
  if (!request)
    return NULL;
  return NewJNIString(env, request->GetURL());
}

JNIEXPORT void JNICALL
Java_org_cef_network_CefRequest_1N_N_1SetURL(JNIEnv* env,
                                             jobject obj,
                                             jstring jurl) {
  CefRefPtr<CefRequest> request =
      GetCefFromJNIObject<CefRequest>(env, obj, "CefRequest");
  if (!request)
    return;
  request->SetURL(GetJNIString(env, jurl));
}

JNIEXPORT void JNICALL
Java_org_cef_network_CefRequest_1N_N_1SetReferrer(JNIEnv* env,
                                                  jobject obj,
                                                  jstring jurl,
                                                  jobject jpolicy) {
  CefRefPtr<CefRequest> request =
      GetCefFromJNIObject<CefRequest>(env, obj, "CefRequest");
  if (!request)
    return;

  cef_referrer_policy_t policy = REFERRER_POLICY_DEFAULT;
  if (jpolicy != NULL) {
    if (IsJNIEnumValue(env, jpolicy,
                       "org/cef/network/CefRequest$ReferrerPolicy",
                       "REFERRER_POLICY_CLEAR_REFERRER_ON_TRANSITION_FROM_"
                       "SECURE_TO_INSECURE")) {
      policy =
          REFERRER_POLICY_CLEAR_REFERRER_ON_TRANSITION_FROM_SECURE_TO_INSECURE;
    } else if (IsJNIEnumValue(env, jpolicy,
                              "org/cef/network/CefRequest$ReferrerPolicy",
                              "REFERRER_POLICY_REDUCE_REFERRER_GRANULARITY_ON_"
                              "TRANSITION_CROSS_ORIGIN")) {
      policy =
          REFERRER_POLICY_REDUCE_REFERRER_GRANULARITY_ON_TRANSITION_CROSS_ORIGIN;
    } else if (IsJNIEnumValue(
                   env, jpolicy, "org/cef/network/CefRequest$ReferrerPolicy",
                   "REFERRER_POLICY_ORIGIN_ONLY_ON_TRANSITION_CROSS_ORIGIN")) {
      policy = REFERRER_POLICY_ORIGIN_ONLY_ON_TRANSITION_CROSS_ORIGIN;
    } else if (IsJNIEnumValue(env, jpolicy,
                              "org/cef/network/CefRequest$ReferrerPolicy",
                              "REFERRER_POLICY_NEVER_CLEAR_REFERRER")) {
      policy = REFERRER_POLICY_NEVER_CLEAR_REFERRER;
    } else if (IsJNIEnumValue(env, jpolicy,
                              "org/cef/network/CefRequest$ReferrerPolicy",
                              "REFERRER_POLICY_ORIGIN")) {
      policy = REFERRER_POLICY_ORIGIN;
    } else if (IsJNIEnumValue(env, jpolicy,
                              "org/cef/network/CefRequest$ReferrerPolicy",
                              "REFERRER_POLICY_CLEAR_REFERRER_ON_TRANSITION_"
                              "CROSS_ORIGIN")) {
      policy = REFERRER_POLICY_CLEAR_REFERRER_ON_TRANSITION_CROSS_ORIGIN;
    } else if (IsJNIEnumValue(env, jpolicy,
                              "org/cef/network/CefRequest$ReferrerPolicy",
                              "REFERRER_POLICY_ORIGIN_CLEAR_ON_TRANSITION_FROM_"
                              "SECURE_TO_INSECURE")) {
      policy =
          REFERRER_POLICY_ORIGIN_CLEAR_ON_TRANSITION_FROM_SECURE_TO_INSECURE;
    } else if (IsJNIEnumValue(env, jpolicy,
                              "org/cef/network/CefRequest$ReferrerPolicy",
                              "REFERRER_POLICY_NO_REFERRER")) {
      policy = REFERRER_POLICY_NO_REFERRER;
    } else if (IsJNIEnumValue(env, jpolicy,
                              "org/cef/network/CefRequest$ReferrerPolicy",
                              "REFERRER_POLICY_LAST_VALUE")) {
      policy = REFERRER_POLICY_LAST_VALUE;
    }
  }

  request->SetReferrer(GetJNIString(env, jurl), policy);
}

JNIEXPORT jstring JNICALL
Java_org_cef_network_CefRequest_1N_N_1GetReferrerURL(JNIEnv* env, jobject obj) {
  CefRefPtr<CefRequest> request =
      GetCefFromJNIObject<CefRequest>(env, obj, "CefRequest");
  if (!request)
    return NULL;

  return NewJNIString(env, request->GetReferrerURL());
}

JNIEXPORT jobject JNICALL
Java_org_cef_network_CefRequest_1N_N_1GetReferrerPolicy(JNIEnv* env,
                                                        jobject obj) {
  CefRefPtr<CefRequest> request =
      GetCefFromJNIObject<CefRequest>(env, obj, "CefRequest");
  if (!request)
    return NULL;

  jobject result = NULL;
  CefRequest::ReferrerPolicy rp = request->GetReferrerPolicy();
  switch (rp) {
    default:
      // same as
      // REFERRER_POLICY_CLEAR_REFERRER_ON_TRANSITION_FROM_SECURE_TO_INSECURE
      JNI_CASE(env, "org/cef/network/CefRequest$ReferrerPolicy",
               REFERRER_POLICY_DEFAULT, result);
      JNI_CASE(
          env, "org/cef/network/CefRequest$ReferrerPolicy",
          REFERRER_POLICY_REDUCE_REFERRER_GRANULARITY_ON_TRANSITION_CROSS_ORIGIN,
          result);
      JNI_CASE(env, "org/cef/network/CefRequest$ReferrerPolicy",
               REFERRER_POLICY_ORIGIN_ONLY_ON_TRANSITION_CROSS_ORIGIN, result);
      JNI_CASE(env, "org/cef/network/CefRequest$ReferrerPolicy",
               REFERRER_POLICY_NEVER_CLEAR_REFERRER, result);
      JNI_CASE(env, "org/cef/network/CefRequest$ReferrerPolicy",
               REFERRER_POLICY_ORIGIN, result);
      JNI_CASE(env, "org/cef/network/CefRequest$ReferrerPolicy",
               REFERRER_POLICY_CLEAR_REFERRER_ON_TRANSITION_CROSS_ORIGIN,
               result);
      JNI_CASE(
          env, "org/cef/network/CefRequest$ReferrerPolicy",
          REFERRER_POLICY_ORIGIN_CLEAR_ON_TRANSITION_FROM_SECURE_TO_INSECURE,
          result);
      JNI_CASE(env, "org/cef/network/CefRequest$ReferrerPolicy",
               REFERRER_POLICY_NO_REFERRER, result);
      JNI_CASE(env, "org/cef/network/CefRequest$ReferrerPolicy",
               REFERRER_POLICY_LAST_VALUE, result);
  }
  return result;
}

JNIEXPORT jstring JNICALL
Java_org_cef_network_CefRequest_1N_N_1GetMethod(JNIEnv* env, jobject obj) {
  CefRefPtr<CefRequest> request =
      GetCefFromJNIObject<CefRequest>(env, obj, "CefRequest");
  if (!request)
    return NULL;
  return NewJNIString(env, request->GetMethod());
}

JNIEXPORT void JNICALL
Java_org_cef_network_CefRequest_1N_N_1SetMethod(JNIEnv* env,
                                                jobject obj,
                                                jstring jmethod) {
  CefRefPtr<CefRequest> request =
      GetCefFromJNIObject<CefRequest>(env, obj, "CefRequest");
  if (!request)
    return;
  request->SetMethod(GetJNIString(env, jmethod));
}

JNIEXPORT jobject JNICALL
Java_org_cef_network_CefRequest_1N_N_1GetPostData(JNIEnv* env, jobject obj) {
  CefRefPtr<CefRequest> request =
      GetCefFromJNIObject<CefRequest>(env, obj, "CefRequest");
  if (!request)
    return NULL;
  CefRefPtr<CefPostData> postData = request->GetPostData();
  if (!postData.get())
    return NULL;

  jobject jpostData = NewJNIObject(env, "org/cef/network/CefPostData_N");
  if (!jpostData)
    return NULL;
  SetCefForJNIObject(env, jpostData, postData.get(), "CefPostData");
  return jpostData;
}

JNIEXPORT void JNICALL
Java_org_cef_network_CefRequest_1N_N_1SetPostData(JNIEnv* env,
                                                  jobject obj,
                                                  jobject jpostData) {
  CefRefPtr<CefRequest> request =
      GetCefFromJNIObject<CefRequest>(env, obj, "CefRequest");
  if (!request)
    return;
  CefRefPtr<CefPostData> postData =
      GetCefFromJNIObject<CefPostData>(env, jpostData, "CefPostData");
  if (!postData.get())
    return;
  request->SetPostData(postData);
}

JNIEXPORT void JNICALL
Java_org_cef_network_CefRequest_1N_N_1GetHeaderMap(JNIEnv* env,
                                                   jobject obj,
                                                   jobject jheaderMap) {
  CefRefPtr<CefRequest> request =
      GetCefFromJNIObject<CefRequest>(env, obj, "CefRequest");
  if (!request)
    return;
  CefRequest::HeaderMap headerMap;
  request->GetHeaderMap(headerMap);

  for (CefRequest::HeaderMap::iterator iter = headerMap.begin();
       iter != headerMap.end(); ++iter) {
    jstring jkey = NewJNIString(env, iter->first);
    jstring jvalue = NewJNIString(env, iter->second);
    jobject returnIgn = NULL;
    JNI_CALL_METHOD(env, jheaderMap, "put",
                    "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;",
                    Object, returnIgn, jkey, jvalue);
    UNUSED(returnIgn);
  }
}

JNIEXPORT void JNICALL
Java_org_cef_network_CefRequest_1N_N_1SetHeaderMap(JNIEnv* env,
                                                   jobject obj,
                                                   jobject jheaderMap) {
  CefRefPtr<CefRequest> request =
      GetCefFromJNIObject<CefRequest>(env, obj, "CefRequest");
  if (!request || !jheaderMap)
    return;

  // public abstract java.util.Set<java.util.Map$Entry<K, V>> entrySet();
  jobject entrySet = NULL;
  JNI_CALL_METHOD(env, jheaderMap, "entrySet", "()Ljava/util/Set;", Object,
                  entrySet);
  if (!entrySet)
    return;

  // public abstract java.lang.Object[] toArray();
  jobject entrySetValues = NULL;
  JNI_CALL_METHOD(env, entrySet, "toArray", "()[Ljava/lang/Object;", Object,
                  entrySetValues);
  if (!entrySetValues)
    return;

  CefRequest::HeaderMap headerMap;
  jint length = env->GetArrayLength((jobjectArray)entrySetValues);
  for (jint i = 0; i < length; i++) {
    jobject mapEntry =
        env->GetObjectArrayElement((jobjectArray)entrySetValues, i);
    if (!mapEntry)
      return;
    jobject key = NULL;
    jobject value = NULL;
    JNI_CALL_METHOD(env, mapEntry, "getKey", "()Ljava/lang/Object;", Object,
                    key);
    JNI_CALL_METHOD(env, mapEntry, "getValue", "()Ljava/lang/Object;", Object,
                    value);
    headerMap.insert(std::make_pair(GetJNIString(env, (jstring)key),
                                    GetJNIString(env, (jstring)value)));
  }
  request->SetHeaderMap(headerMap);
}

JNIEXPORT void JNICALL
Java_org_cef_network_CefRequest_1N_N_1Set(JNIEnv* env,
                                          jobject obj,
                                          jstring jurl,
                                          jstring jmethod,
                                          jobject jpostData,
                                          jobject jheaderMap) {
  Java_org_cef_network_CefRequest_1N_N_1SetURL(env, obj, jurl);
  Java_org_cef_network_CefRequest_1N_N_1SetMethod(env, obj, jmethod);
  Java_org_cef_network_CefRequest_1N_N_1SetPostData(env, obj, jpostData);
  Java_org_cef_network_CefRequest_1N_N_1SetHeaderMap(env, obj, jheaderMap);
}

JNIEXPORT jint JNICALL
Java_org_cef_network_CefRequest_1N_N_1GetFlags(JNIEnv* env, jobject obj) {
  CefRefPtr<CefRequest> request =
      GetCefFromJNIObject<CefRequest>(env, obj, "CefRequest");
  if (!request)
    return 0;
  return request->GetFlags();
}

JNIEXPORT void JNICALL
Java_org_cef_network_CefRequest_1N_N_1SetFlags(JNIEnv* env,
                                               jobject obj,
                                               jint jflags) {
  CefRefPtr<CefRequest> request =
      GetCefFromJNIObject<CefRequest>(env, obj, "CefRequest");
  if (!request)
    return;
  request->SetFlags((int)jflags);
}

JNIEXPORT jstring JNICALL
Java_org_cef_network_CefRequest_1N_N_1GetFirstPartyForCookies(JNIEnv* env,
                                                              jobject obj) {
  CefRefPtr<CefRequest> request =
      GetCefFromJNIObject<CefRequest>(env, obj, "CefRequest");
  if (!request)
    return NULL;
  return NewJNIString(env, request->GetFirstPartyForCookies());
}

JNIEXPORT void JNICALL
Java_org_cef_network_CefRequest_1N_N_1SetFirstPartyForCookies(JNIEnv* env,
                                                              jobject obj,
                                                              jstring jcookie) {
  CefRefPtr<CefRequest> request =
      GetCefFromJNIObject<CefRequest>(env, obj, "CefRequest");
  if (!request)
    return;
  request->SetFirstPartyForCookies(GetJNIString(env, jcookie));
}

JNIEXPORT jobject JNICALL
Java_org_cef_network_CefRequest_1N_N_1GetResourceType(JNIEnv* env,
                                                      jobject obj) {
  CefRefPtr<CefRequest> request =
      GetCefFromJNIObject<CefRequest>(env, obj, "CefRequest");
  if (!request)
    return NULL;

  jobject result = NULL;
  CefRequest::ResourceType rt = request->GetResourceType();
  switch (rt) {
    JNI_CASE(env, "org/cef/network/CefRequest$ResourceType", RT_MAIN_FRAME,
             result);
    JNI_CASE(env, "org/cef/network/CefRequest$ResourceType", RT_SUB_FRAME,
             result);
    JNI_CASE(env, "org/cef/network/CefRequest$ResourceType", RT_STYLESHEET,
             result);
    JNI_CASE(env, "org/cef/network/CefRequest$ResourceType", RT_SCRIPT, result);
    JNI_CASE(env, "org/cef/network/CefRequest$ResourceType", RT_IMAGE, result);
    JNI_CASE(env, "org/cef/network/CefRequest$ResourceType", RT_FONT_RESOURCE,
             result);
    default:
      JNI_CASE(env, "org/cef/network/CefRequest$ResourceType", RT_SUB_RESOURCE,
               result);
      JNI_CASE(env, "org/cef/network/CefRequest$ResourceType", RT_OBJECT,
               result);
      JNI_CASE(env, "org/cef/network/CefRequest$ResourceType", RT_MEDIA,
               result);
      JNI_CASE(env, "org/cef/network/CefRequest$ResourceType", RT_WORKER,
               result);
      JNI_CASE(env, "org/cef/network/CefRequest$ResourceType", RT_SHARED_WORKER,
               result);
      JNI_CASE(env, "org/cef/network/CefRequest$ResourceType", RT_PREFETCH,
               result);
      JNI_CASE(env, "org/cef/network/CefRequest$ResourceType", RT_FAVICON,
               result);
      JNI_CASE(env, "org/cef/network/CefRequest$ResourceType", RT_XHR, result);
  }
  return result;
}

JNIEXPORT jobject JNICALL
Java_org_cef_network_CefRequest_1N_N_1GetTransitionType(JNIEnv* env,
                                                        jobject obj) {
  CefRefPtr<CefRequest> request =
      GetCefFromJNIObject<CefRequest>(env, obj, "CefRequest");
  if (!request)
    return NULL;

  CefRequest::TransitionType transitionType = request->GetTransitionType();

  return NewJNITransitionType(env, transitionType);
}

JNIEXPORT void JNICALL
Java_org_cef_network_CefRequest_1N_N_1CefRequest_1DTOR(JNIEnv* env,
                                                       jobject obj) {
  SetCefForJNIObject<CefRequest>(env, obj, NULL, "CefRequest");
}
