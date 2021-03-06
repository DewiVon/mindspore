/**
 * Copyright 2021 Huawei Technologies Co., Ltd
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

#include "src/ops/crop_and_resize.h"
#include "src/ops/primitive_c.h"
#include "src/ops/populate/populate_register.h"
#include "nnacl/resize_parameter.h"
namespace mindspore {
namespace lite {
OpParameter *PopulateCropAndResizeParameter(const mindspore::lite::PrimitiveC *primitive) {
  CropAndResizeParameter *crop_resize_param =
    reinterpret_cast<CropAndResizeParameter *>(malloc(sizeof(CropAndResizeParameter)));
  if (crop_resize_param == nullptr) {
    MS_LOG(ERROR) << "malloc CropAndResizeParameter failed.";
    return nullptr;
  }
  memset(crop_resize_param, 0, sizeof(CropAndResizeParameter));
  crop_resize_param->op_parameter_.type_ = primitive->Type();
  auto param = reinterpret_cast<mindspore::lite::CropAndResize *>(const_cast<mindspore::lite::PrimitiveC *>(primitive));
  crop_resize_param->method_ = static_cast<int>(param->GetMethod());
  crop_resize_param->extrapolation_value_ = param->GetExtrapolationValue();
  return reinterpret_cast<OpParameter *>(crop_resize_param);
}

Registry CropAndResizeParameterRegistry(schema::PrimitiveType_CropAndResize, PopulateCropAndResizeParameter);
}  // namespace lite
}  // namespace mindspore
