// Generated by cpp11: do not edit by hand
// clang-format off

#include "flowWorkspace_types.h"
#include "cpp11/declarations.hpp"

// cytoframeAPI.cpp
void del_rownames(cpp11::external_pointer<CytoFrameView> fr);
extern "C" SEXP _flowWorkspace_del_rownames(SEXP fr) {
  BEGIN_CPP11
    del_rownames(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr));
    return R_NilValue;
  END_CPP11
}
// cytoframeAPI.cpp
void set_rownames(cpp11::external_pointer<CytoFrameView> fr, vector<string> val);
extern "C" SEXP _flowWorkspace_set_rownames(SEXP fr, SEXP val) {
  BEGIN_CPP11
    set_rownames(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr), cpp11::as_cpp<cpp11::decay_t<vector<string>>>(val));
    return R_NilValue;
  END_CPP11
}
// cytoframeAPI.cpp
vector<string> get_rownames(cpp11::external_pointer<CytoFrameView> fr);
extern "C" SEXP _flowWorkspace_get_rownames(SEXP fr) {
  BEGIN_CPP11
    return cpp11::as_sexp(get_rownames(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr)));
  END_CPP11
}
// cytoframeAPI.cpp
string backend_type(cpp11::external_pointer<CytoFrameView> fr);
extern "C" SEXP _flowWorkspace_backend_type(SEXP fr) {
  BEGIN_CPP11
    return cpp11::as_sexp(backend_type(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr)));
  END_CPP11
}
// cytoframeAPI.cpp
bool cf_is_indexed(cpp11::external_pointer<CytoFrameView> fr);
extern "C" SEXP _flowWorkspace_cf_is_indexed(SEXP fr) {
  BEGIN_CPP11
    return cpp11::as_sexp(cf_is_indexed(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr)));
  END_CPP11
}
// cytoframeAPI.cpp
void cf_scale_time_channel_cpp(cpp11::external_pointer<CytoFrameView> fr);
extern "C" SEXP _flowWorkspace_cf_scale_time_channel_cpp(SEXP fr) {
  BEGIN_CPP11
    cf_scale_time_channel_cpp(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr));
    return R_NilValue;
  END_CPP11
}
// cytoframeAPI.cpp
void cf_set_readonly(cpp11::external_pointer<CytoFrameView> fr, bool flag);
extern "C" SEXP _flowWorkspace_cf_set_readonly(SEXP fr, SEXP flag) {
  BEGIN_CPP11
    cf_set_readonly(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr), cpp11::as_cpp<cpp11::decay_t<bool>>(flag));
    return R_NilValue;
  END_CPP11
}
// cytoframeAPI.cpp
void cf_flush_meta_cpp(cpp11::external_pointer<CytoFrameView> fr);
extern "C" SEXP _flowWorkspace_cf_flush_meta_cpp(SEXP fr) {
  BEGIN_CPP11
    cf_flush_meta_cpp(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr));
    return R_NilValue;
  END_CPP11
}
// cytoframeAPI.cpp
void cf_load_meta_cpp(cpp11::external_pointer<CytoFrameView> fr);
extern "C" SEXP _flowWorkspace_cf_load_meta_cpp(SEXP fr) {
  BEGIN_CPP11
    cf_load_meta_cpp(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr));
    return R_NilValue;
  END_CPP11
}
// cytoframeAPI.cpp
string get_uri(cpp11::external_pointer<CytoFrameView> fr);
extern "C" SEXP _flowWorkspace_get_uri(SEXP fr) {
  BEGIN_CPP11
    return cpp11::as_sexp(get_uri(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr)));
  END_CPP11
}
// cytoframeAPI.cpp
cpp11::external_pointer<CytoFrameView> realize_view_cytoframe(cpp11::external_pointer<CytoFrameView> fr, string filename);
extern "C" SEXP _flowWorkspace_realize_view_cytoframe(SEXP fr, SEXP filename) {
  BEGIN_CPP11
    return cpp11::as_sexp(realize_view_cytoframe(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr), cpp11::as_cpp<cpp11::decay_t<string>>(filename)));
  END_CPP11
}
// cytoframeAPI.cpp
cpp11::external_pointer<CytoFrameView> copy_view_cytoframe(cpp11::external_pointer<CytoFrameView> fr);
extern "C" SEXP _flowWorkspace_copy_view_cytoframe(SEXP fr) {
  BEGIN_CPP11
    return cpp11::as_sexp(copy_view_cytoframe(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr)));
  END_CPP11
}
// cytoframeAPI.cpp
void subset_cytoframe_by_rows(cpp11::external_pointer<CytoFrameView> fr, vector<unsigned> idx);
extern "C" SEXP _flowWorkspace_subset_cytoframe_by_rows(SEXP fr, SEXP idx) {
  BEGIN_CPP11
    subset_cytoframe_by_rows(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr), cpp11::as_cpp<cpp11::decay_t<vector<unsigned>>>(idx));
    return R_NilValue;
  END_CPP11
}
// cytoframeAPI.cpp
void subset_cytoframe_by_cols(cpp11::external_pointer<CytoFrameView> fr, vector<unsigned> idx);
extern "C" SEXP _flowWorkspace_subset_cytoframe_by_cols(SEXP fr, SEXP idx) {
  BEGIN_CPP11
    subset_cytoframe_by_cols(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr), cpp11::as_cpp<cpp11::decay_t<vector<unsigned>>>(idx));
    return R_NilValue;
  END_CPP11
}
// cytoframeAPI.cpp
void frm_compensate(cpp11::external_pointer<CytoFrameView> fr, cpp11::doubles_matrix spillover);
extern "C" SEXP _flowWorkspace_frm_compensate(SEXP fr, SEXP spillover) {
  BEGIN_CPP11
    frm_compensate(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr), cpp11::as_cpp<cpp11::decay_t<cpp11::doubles_matrix>>(spillover));
    return R_NilValue;
  END_CPP11
}
// cytoframeAPI.cpp
void write_to_disk(cpp11::external_pointer<CytoFrameView> fr, string filename, bool ish5);
extern "C" SEXP _flowWorkspace_write_to_disk(SEXP fr, SEXP filename, SEXP ish5) {
  BEGIN_CPP11
    write_to_disk(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr), cpp11::as_cpp<cpp11::decay_t<string>>(filename), cpp11::as_cpp<cpp11::decay_t<bool>>(ish5));
    return R_NilValue;
  END_CPP11
}
// cytoframeAPI.cpp
cpp11::external_pointer<CytoFrameView> load_cf(string url, bool readonly, bool on_disk);
extern "C" SEXP _flowWorkspace_load_cf(SEXP url, SEXP readonly, SEXP on_disk) {
  BEGIN_CPP11
    return cpp11::as_sexp(load_cf(cpp11::as_cpp<cpp11::decay_t<string>>(url), cpp11::as_cpp<cpp11::decay_t<bool>>(readonly), cpp11::as_cpp<cpp11::decay_t<bool>>(on_disk)));
  END_CPP11
}
// cytoframeAPI.cpp
cpp11::external_pointer<CytoFrameView> cf_to_memcf(cpp11::external_pointer<CytoFrameView> fr);
extern "C" SEXP _flowWorkspace_cf_to_memcf(SEXP fr) {
  BEGIN_CPP11
    return cpp11::as_sexp(cf_to_memcf(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr)));
  END_CPP11
}
// cytoframeAPI.cpp
void setMarker(cpp11::external_pointer<CytoFrameView> fr, string channel, string marker);
extern "C" SEXP _flowWorkspace_setMarker(SEXP fr, SEXP channel, SEXP marker) {
  BEGIN_CPP11
    setMarker(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr), cpp11::as_cpp<cpp11::decay_t<string>>(channel), cpp11::as_cpp<cpp11::decay_t<string>>(marker));
    return R_NilValue;
  END_CPP11
}
// cytoframeAPI.cpp
void set_all_channels(cpp11::external_pointer<CytoFrameView> fr, vector<string> new_names);
extern "C" SEXP _flowWorkspace_set_all_channels(SEXP fr, SEXP new_names) {
  BEGIN_CPP11
    set_all_channels(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr), cpp11::as_cpp<cpp11::decay_t<vector<string>>>(new_names));
    return R_NilValue;
  END_CPP11
}
// cytoframeAPI.cpp
void setChannel(cpp11::external_pointer<CytoFrameView> fr, string old, string new_name);
extern "C" SEXP _flowWorkspace_setChannel(SEXP fr, SEXP old, SEXP new_name) {
  BEGIN_CPP11
    setChannel(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr), cpp11::as_cpp<cpp11::decay_t<string>>(old), cpp11::as_cpp<cpp11::decay_t<string>>(new_name));
    return R_NilValue;
  END_CPP11
}
// cytoframeAPI.cpp
vector<string> get_channels(cpp11::external_pointer<CytoFrameView> fr);
extern "C" SEXP _flowWorkspace_get_channels(SEXP fr) {
  BEGIN_CPP11
    return cpp11::as_sexp(get_channels(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr)));
  END_CPP11
}
// cytoframeAPI.cpp
cpp11::external_pointer<CytoFrameView> append_cols(cpp11::external_pointer<CytoFrameView> fr, vector<string> new_colnames, cpp11::doubles_matrix new_cols_mat);
extern "C" SEXP _flowWorkspace_append_cols(SEXP fr, SEXP new_colnames, SEXP new_cols_mat) {
  BEGIN_CPP11
    return cpp11::as_sexp(append_cols(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr), cpp11::as_cpp<cpp11::decay_t<vector<string>>>(new_colnames), cpp11::as_cpp<cpp11::decay_t<cpp11::doubles_matrix>>(new_cols_mat)));
  END_CPP11
}
// cytoframeAPI.cpp
cpp11::external_pointer<CytoFrameView> parseFCS(string filename, SEXP configr, bool text_only, string format, string uri);
extern "C" SEXP _flowWorkspace_parseFCS(SEXP filename, SEXP configr, SEXP text_only, SEXP format, SEXP uri) {
  BEGIN_CPP11
    return cpp11::as_sexp(parseFCS(cpp11::as_cpp<cpp11::decay_t<string>>(filename), cpp11::as_cpp<cpp11::decay_t<SEXP>>(configr), cpp11::as_cpp<cpp11::decay_t<bool>>(text_only), cpp11::as_cpp<cpp11::decay_t<string>>(format), cpp11::as_cpp<cpp11::decay_t<string>>(uri)));
  END_CPP11
}
// cytoframeAPI.cpp
cpp11::doubles_matrix cf_getData(cpp11::external_pointer<CytoFrameView> fr);
extern "C" SEXP _flowWorkspace_cf_getData(SEXP fr) {
  BEGIN_CPP11
    return cpp11::as_sexp(cf_getData(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr)));
  END_CPP11
}
// cytoframeAPI.cpp
void cf_setData(cpp11::external_pointer<CytoFrameView> fr, cpp11::doubles_matrix rmat);
extern "C" SEXP _flowWorkspace_cf_setData(SEXP fr, SEXP rmat) {
  BEGIN_CPP11
    cf_setData(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr), cpp11::as_cpp<cpp11::decay_t<cpp11::doubles_matrix>>(rmat));
    return R_NilValue;
  END_CPP11
}
// cytoframeAPI.cpp
void cf_transform_data(cpp11::external_pointer<CytoFrameView> fr, cpp11::list translist);
extern "C" SEXP _flowWorkspace_cf_transform_data(SEXP fr, SEXP translist) {
  BEGIN_CPP11
    cf_transform_data(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr), cpp11::as_cpp<cpp11::decay_t<cpp11::list>>(translist));
    return R_NilValue;
  END_CPP11
}
// cytoframeAPI.cpp
string cf_getKeyword(cpp11::external_pointer<CytoFrameView> fr, string key);
extern "C" SEXP _flowWorkspace_cf_getKeyword(SEXP fr, SEXP key) {
  BEGIN_CPP11
    return cpp11::as_sexp(cf_getKeyword(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr), cpp11::as_cpp<cpp11::decay_t<string>>(key)));
  END_CPP11
}
// cytoframeAPI.cpp
SEXP cf_getKeywords(cpp11::external_pointer<CytoFrameView> fr);
extern "C" SEXP _flowWorkspace_cf_getKeywords(SEXP fr) {
  BEGIN_CPP11
    return cpp11::as_sexp(cf_getKeywords(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr)));
  END_CPP11
}
// cytoframeAPI.cpp
void cf_setKeywords(cpp11::external_pointer<CytoFrameView> fr, cpp11::list_of<cpp11::r_string> keys);
extern "C" SEXP _flowWorkspace_cf_setKeywords(SEXP fr, SEXP keys) {
  BEGIN_CPP11
    cf_setKeywords(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr), cpp11::as_cpp<cpp11::decay_t<cpp11::list_of<cpp11::r_string>>>(keys));
    return R_NilValue;
  END_CPP11
}
// cytoframeAPI.cpp
void cf_setKeywordsSubset(cpp11::external_pointer<CytoFrameView> fr, cpp11::strings keys, cpp11::strings values);
extern "C" SEXP _flowWorkspace_cf_setKeywordsSubset(SEXP fr, SEXP keys, SEXP values) {
  BEGIN_CPP11
    cf_setKeywordsSubset(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr), cpp11::as_cpp<cpp11::decay_t<cpp11::strings>>(keys), cpp11::as_cpp<cpp11::decay_t<cpp11::strings>>(values));
    return R_NilValue;
  END_CPP11
}
// cytoframeAPI.cpp
void cf_renameKeywords(cpp11::external_pointer<CytoFrameView> fr, cpp11::strings old_keys, cpp11::strings new_keys);
extern "C" SEXP _flowWorkspace_cf_renameKeywords(SEXP fr, SEXP old_keys, SEXP new_keys) {
  BEGIN_CPP11
    cf_renameKeywords(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr), cpp11::as_cpp<cpp11::decay_t<cpp11::strings>>(old_keys), cpp11::as_cpp<cpp11::decay_t<cpp11::strings>>(new_keys));
    return R_NilValue;
  END_CPP11
}
// cytoframeAPI.cpp
void cf_removeKeywords(cpp11::external_pointer<CytoFrameView> fr, cpp11::strings keys);
extern "C" SEXP _flowWorkspace_cf_removeKeywords(SEXP fr, SEXP keys) {
  BEGIN_CPP11
    cf_removeKeywords(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr), cpp11::as_cpp<cpp11::decay_t<cpp11::strings>>(keys));
    return R_NilValue;
  END_CPP11
}
// cytoframeAPI.cpp
int getncol(cpp11::external_pointer<CytoFrameView> fr);
extern "C" SEXP _flowWorkspace_getncol(SEXP fr) {
  BEGIN_CPP11
    return cpp11::as_sexp(getncol(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr)));
  END_CPP11
}
// cytoframeAPI.cpp
int getnrow(cpp11::external_pointer<CytoFrameView> fr);
extern "C" SEXP _flowWorkspace_getnrow(SEXP fr) {
  BEGIN_CPP11
    return cpp11::as_sexp(getnrow(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<CytoFrameView>>>(fr)));
  END_CPP11
}

extern "C" {
/* .Call calls */
extern SEXP _flowWorkspace_append_cols(SEXP, SEXP, SEXP);
extern SEXP _flowWorkspace_backend_type(SEXP);
extern SEXP _flowWorkspace_cf_flush_meta_cpp(SEXP);
extern SEXP _flowWorkspace_cf_getData(SEXP);
extern SEXP _flowWorkspace_cf_getKeyword(SEXP, SEXP);
extern SEXP _flowWorkspace_cf_getKeywords(SEXP);
extern SEXP _flowWorkspace_cf_is_indexed(SEXP);
extern SEXP _flowWorkspace_cf_load_meta_cpp(SEXP);
extern SEXP _flowWorkspace_cf_removeKeywords(SEXP, SEXP);
extern SEXP _flowWorkspace_cf_renameKeywords(SEXP, SEXP, SEXP);
extern SEXP _flowWorkspace_cf_scale_time_channel_cpp(SEXP);
extern SEXP _flowWorkspace_cf_set_readonly(SEXP, SEXP);
extern SEXP _flowWorkspace_cf_setData(SEXP, SEXP);
extern SEXP _flowWorkspace_cf_setKeywords(SEXP, SEXP);
extern SEXP _flowWorkspace_cf_setKeywordsSubset(SEXP, SEXP, SEXP);
extern SEXP _flowWorkspace_cf_to_memcf(SEXP);
extern SEXP _flowWorkspace_cf_transform_data(SEXP, SEXP);
extern SEXP _flowWorkspace_copy_view_cytoframe(SEXP);
extern SEXP _flowWorkspace_del_rownames(SEXP);
extern SEXP _flowWorkspace_frm_compensate(SEXP, SEXP);
extern SEXP _flowWorkspace_get_channels(SEXP);
extern SEXP _flowWorkspace_get_rownames(SEXP);
extern SEXP _flowWorkspace_get_uri(SEXP);
extern SEXP _flowWorkspace_getncol(SEXP);
extern SEXP _flowWorkspace_getnrow(SEXP);
extern SEXP _flowWorkspace_load_cf(SEXP, SEXP, SEXP);
extern SEXP _flowWorkspace_parseFCS(SEXP, SEXP, SEXP, SEXP, SEXP);
extern SEXP _flowWorkspace_realize_view_cytoframe(SEXP, SEXP);
extern SEXP _flowWorkspace_set_all_channels(SEXP, SEXP);
extern SEXP _flowWorkspace_set_rownames(SEXP, SEXP);
extern SEXP _flowWorkspace_setChannel(SEXP, SEXP, SEXP);
extern SEXP _flowWorkspace_setMarker(SEXP, SEXP, SEXP);
extern SEXP _flowWorkspace_subset_cytoframe_by_cols(SEXP, SEXP);
extern SEXP _flowWorkspace_subset_cytoframe_by_rows(SEXP, SEXP);
extern SEXP _flowWorkspace_write_to_disk(SEXP, SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"_flowWorkspace_append_cols",               (DL_FUNC) &_flowWorkspace_append_cols,               3},
    {"_flowWorkspace_backend_type",              (DL_FUNC) &_flowWorkspace_backend_type,              1},
    {"_flowWorkspace_cf_flush_meta_cpp",         (DL_FUNC) &_flowWorkspace_cf_flush_meta_cpp,         1},
    {"_flowWorkspace_cf_getData",                (DL_FUNC) &_flowWorkspace_cf_getData,                1},
    {"_flowWorkspace_cf_getKeyword",             (DL_FUNC) &_flowWorkspace_cf_getKeyword,             2},
    {"_flowWorkspace_cf_getKeywords",            (DL_FUNC) &_flowWorkspace_cf_getKeywords,            1},
    {"_flowWorkspace_cf_is_indexed",             (DL_FUNC) &_flowWorkspace_cf_is_indexed,             1},
    {"_flowWorkspace_cf_load_meta_cpp",          (DL_FUNC) &_flowWorkspace_cf_load_meta_cpp,          1},
    {"_flowWorkspace_cf_removeKeywords",         (DL_FUNC) &_flowWorkspace_cf_removeKeywords,         2},
    {"_flowWorkspace_cf_renameKeywords",         (DL_FUNC) &_flowWorkspace_cf_renameKeywords,         3},
    {"_flowWorkspace_cf_scale_time_channel_cpp", (DL_FUNC) &_flowWorkspace_cf_scale_time_channel_cpp, 1},
    {"_flowWorkspace_cf_set_readonly",           (DL_FUNC) &_flowWorkspace_cf_set_readonly,           2},
    {"_flowWorkspace_cf_setData",                (DL_FUNC) &_flowWorkspace_cf_setData,                2},
    {"_flowWorkspace_cf_setKeywords",            (DL_FUNC) &_flowWorkspace_cf_setKeywords,            2},
    {"_flowWorkspace_cf_setKeywordsSubset",      (DL_FUNC) &_flowWorkspace_cf_setKeywordsSubset,      3},
    {"_flowWorkspace_cf_to_memcf",               (DL_FUNC) &_flowWorkspace_cf_to_memcf,               1},
    {"_flowWorkspace_cf_transform_data",         (DL_FUNC) &_flowWorkspace_cf_transform_data,         2},
    {"_flowWorkspace_copy_view_cytoframe",       (DL_FUNC) &_flowWorkspace_copy_view_cytoframe,       1},
    {"_flowWorkspace_del_rownames",              (DL_FUNC) &_flowWorkspace_del_rownames,              1},
    {"_flowWorkspace_frm_compensate",            (DL_FUNC) &_flowWorkspace_frm_compensate,            2},
    {"_flowWorkspace_get_channels",              (DL_FUNC) &_flowWorkspace_get_channels,              1},
    {"_flowWorkspace_get_rownames",              (DL_FUNC) &_flowWorkspace_get_rownames,              1},
    {"_flowWorkspace_get_uri",                   (DL_FUNC) &_flowWorkspace_get_uri,                   1},
    {"_flowWorkspace_getncol",                   (DL_FUNC) &_flowWorkspace_getncol,                   1},
    {"_flowWorkspace_getnrow",                   (DL_FUNC) &_flowWorkspace_getnrow,                   1},
    {"_flowWorkspace_load_cf",                   (DL_FUNC) &_flowWorkspace_load_cf,                   3},
    {"_flowWorkspace_parseFCS",                  (DL_FUNC) &_flowWorkspace_parseFCS,                  5},
    {"_flowWorkspace_realize_view_cytoframe",    (DL_FUNC) &_flowWorkspace_realize_view_cytoframe,    2},
    {"_flowWorkspace_set_all_channels",          (DL_FUNC) &_flowWorkspace_set_all_channels,          2},
    {"_flowWorkspace_set_rownames",              (DL_FUNC) &_flowWorkspace_set_rownames,              2},
    {"_flowWorkspace_setChannel",                (DL_FUNC) &_flowWorkspace_setChannel,                3},
    {"_flowWorkspace_setMarker",                 (DL_FUNC) &_flowWorkspace_setMarker,                 3},
    {"_flowWorkspace_subset_cytoframe_by_cols",  (DL_FUNC) &_flowWorkspace_subset_cytoframe_by_cols,  2},
    {"_flowWorkspace_subset_cytoframe_by_rows",  (DL_FUNC) &_flowWorkspace_subset_cytoframe_by_rows,  2},
    {"_flowWorkspace_write_to_disk",             (DL_FUNC) &_flowWorkspace_write_to_disk,             3},
    {NULL, NULL, 0}
};
}

extern "C" void R_init_flowWorkspace(DllInfo* dll){
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
  R_forceSymbols(dll, TRUE);
}
