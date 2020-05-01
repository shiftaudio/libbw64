/**
 * @file bw64.hpp
 *
 * libbw64 main header file. This should be the only file you need to include
 * into your user code.
 */
#pragma once
#include "reader.hpp"
#include "writer.hpp"

namespace bw64 {

  /**
   * @brief Open a BW64 file for reading
   *
   * @param filename path of the file to read
   *
   * Convenience function to open a BW64 file for reading.
   *
   * @returns `unique_ptr` to a Bw64Reader instance that is ready to read
   * samples.
   */
#if __cplusplus >= 201703L
  inline std::unique_ptr<Bw64Reader> readFile(std::filesystem::path const& filename)
#else
  inline std::unique_ptr<Bw64Reader> readFile(std::string const& filename)
#endif
  {
    return std::unique_ptr<Bw64Reader>(new Bw64Reader(filename));
  }

  /**
   * @brief Open a BW64 file for writing
   *
   * Convenience function to open a new BW64 file for writing, adding `axml` and
   * `chna` chunks.
   *
   * If passed to this function, the `axml` and `chna` chunks will be added to
   * the BW64 file *before* the actual data chunk, which is the recommended
   * practice if all components are already known before writing a file.
   *
   * @param filename path of the file to write
   * @param channels the channel count of the new file
   * @param sampleRate the samplerate of the new file
   * @param bitDepth target bitdepth of the new file
   * @param chnaChunk Channel allocation chunk to include, if any
   * @param axmlChunk AXML chunk to include, if any
   *
   * @returns `unique_ptr` to a Bw64Writer instance that is ready to write
   * samples.
   *
   */

#if __cplusplus >= 201703L
  inline std::unique_ptr<Bw64Writer> writeFile(
      std::filesystem::path const& filename,
      uint16_t channels = 1u,
      uint32_t sampleRate = 48000u,
      uint16_t bitDepth = 24u,
      std::shared_ptr<ChnaChunk> chnaChunk = nullptr,
      std::shared_ptr<AxmlChunk> axmlChunk = nullptr) 
#else
  inline std::unique_ptr<Bw64Writer> writeFile(
      std::string const& filename,
      uint16_t channels = 1u,
      uint32_t sampleRate = 48000u,
      uint16_t bitDepth = 24u,
      std::shared_ptr<ChnaChunk> chnaChunk = nullptr,
      std::shared_ptr<AxmlChunk> axmlChunk = nullptr) 
#endif
  {
    std::vector<std::shared_ptr<Chunk>> additionalChunks;
    if (chnaChunk) {
      additionalChunks.push_back(chnaChunk);
    }
    if (axmlChunk) {
      additionalChunks.push_back(axmlChunk);
    }
    return std::unique_ptr<Bw64Writer>(new Bw64Writer(
        filename, channels, sampleRate, bitDepth, additionalChunks));
  }

}  // namespace bw64
