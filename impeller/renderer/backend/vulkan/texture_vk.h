// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_IMPELLER_RENDERER_BACKEND_VULKAN_TEXTURE_VK_H_
#define FLUTTER_IMPELLER_RENDERER_BACKEND_VULKAN_TEXTURE_VK_H_

#include "impeller/base/backend_cast.h"
#include "impeller/core/texture.h"
#include "impeller/renderer/backend/vulkan/context_vk.h"
#include "impeller/renderer/backend/vulkan/device_buffer_vk.h"
#include "impeller/renderer/backend/vulkan/formats_vk.h"
#include "impeller/renderer/backend/vulkan/texture_source_vk.h"
#include "impeller/renderer/backend/vulkan/vk.h"

namespace impeller {

class TextureVK final : public Texture, public BackendCast<TextureVK, Texture> {
 public:
  TextureVK(std::weak_ptr<Context> context,
            std::shared_ptr<TextureSourceVK> source);

  // |Texture|
  ~TextureVK() override;

  vk::Image GetImage() const;

  vk::ImageView GetImageView() const;

  bool SetLayout(const BarrierVK& barrier) const;

  vk::ImageLayout SetLayoutWithoutEncoding(vk::ImageLayout layout) const;

  vk::ImageLayout GetLayout() const;

  std::shared_ptr<const TextureSourceVK> GetTextureSource() const;

  // |Texture|
  ISize GetSize() const override;

 private:
  std::weak_ptr<Context> context_;
  std::shared_ptr<TextureSourceVK> source_;

  // |Texture|
  void SetLabel(std::string_view label) override;

  // |Texture|
  bool OnSetContents(const uint8_t* contents,
                     size_t length,
                     size_t slice) override;

  // |Texture|
  bool OnSetContents(std::shared_ptr<const fml::Mapping> mapping,
                     size_t slice) override;

  // |Texture|
  bool IsValid() const override;

  TextureVK(const TextureVK&) = delete;

  TextureVK& operator=(const TextureVK&) = delete;
};

}  // namespace impeller

#endif  // FLUTTER_IMPELLER_RENDERER_BACKEND_VULKAN_TEXTURE_VK_H_
