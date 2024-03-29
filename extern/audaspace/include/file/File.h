/*******************************************************************************
 * Copyright 2009-2016 Jörg Müller
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

#pragma once

/**
 * @file File.h
 * @ingroup file
 * The File class.
 */

#include "ISound.h"
#include "FileInfo.h"

#include <string>
#include <memory>
#include <vector>

AUD_NAMESPACE_BEGIN

class Buffer;

/**
 * The File sound tries to read a sound file via all available file inputs
 * that have been registered in the FileManager class.
 */
class AUD_API File : public ISound
{
private:
	/**
	 * The filename of the sound source file.
	 */
	std::string m_filename;

	/**
	 * The buffer to read from.
	 */
	std::shared_ptr<Buffer> m_buffer;

	/**
	 * The index of the stream within the file if it contains multiple.
	 * The first audio stream in the file has index 0 and the index increments by one
	 * for every other audio stream in the file. Other types of streams in the file
	 * do not count.
	 */
	int m_stream;

	// delete copy constructor and operator=
	File(const File&) = delete;
	File& operator=(const File&) = delete;

public:
	/**
	 * Creates a new sound.
	 * The file is read from the file system using the given path.
	 * \param filename The sound file path.
	 * \param stream The index of the audio stream within the file if it contains multiple audio streams.
	 */
	File(const std::string &filename, int stream = 0);

	/**
	 * Creates a new sound.
	 * The file is read from memory using the supplied buffer.
	 * \param buffer The buffer to read from.
	 * \param size The size of the buffer.
	 * \param stream The index of the audio stream within the file if it contains multiple audio streams.
	 */
	File(const data_t* buffer, int size, int stream = 0);

	/**
	 * Queries the streams of the file.
	 * \return A vector with as many streams as there are in the file.
	 * \exception Exception Thrown if the file specified cannot be read.
	 */
	std::vector<StreamInfo> queryStreams();

	virtual std::shared_ptr<IReader> createReader();
};

AUD_NAMESPACE_END
