/**
 * Copyright 2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "tools/converter/parser/tflite/tflite_expand_dims_parser.h"
#include <vector>
#include <memory>
#include <map>

namespace mindspore {
namespace lite {
STATUS TfliteExpandDimsParser::Parse(TfliteTensorsInfo *tensors_info,
                                     const std::unique_ptr<tflite::OperatorT> &tflite_op,
                                     const std::unique_ptr<tflite::ModelT> &tflite_model, schema::CNodeT *op) {
  MS_LOG(DEBUG) << "parse TfliteExpandDimsParser";
  if (op == nullptr) {
    MS_LOG(ERROR) << "op is null";
    return RET_NULL_PTR;
  }
  op->primitive = std::make_unique<schema::PrimitiveT>();
  if (op->primitive == nullptr) {
    MS_LOG(ERROR) << "op->primitive is null";
    return RET_NULL_PTR;
  }

  std::unique_ptr<schema::ExpandDimsT> attr = std::make_unique<schema::ExpandDimsT>();
  if (attr == nullptr) {
    MS_LOG(ERROR) << "new op failed";
    return RET_NULL_PTR;
  }
  std::vector<int> dims;
  if (GetTfliteData(tflite_op->inputs[1], tflite_model->subgraphs[0]->tensors, tflite_model->buffers, dims)) {
    MS_LOG(ERROR) << "get expand_dims -> dim failed";
    return RET_ERROR;
  }
  attr->dim = dims[0];
  op->primitive->value.type = schema::PrimitiveType_ExpandDims;
  op->primitive->value.value = attr.release();
  AddOpInput(op, tensors_info, tflite_op->inputs[0], tflite_model->subgraphs[0]->tensors.size(),
             schema::Format::Format_NHWC);
  AddOpOutput(op, tensors_info, tflite_op->outputs[0], tflite_model->subgraphs[0]->tensors.size(),
              schema::Format::Format_NHWC);
  return RET_OK;
}
TfliteNodeRegister g_tfliteExpandDimsParser("ExpandDims", new TfliteExpandDimsParser());
}  // namespace lite
}  // namespace mindspore
