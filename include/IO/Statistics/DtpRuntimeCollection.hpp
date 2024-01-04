/*
 * DtpRuntimeCollection.hpp
 *
 *  Created on: Feb 26, 2019
 *      Author: Franziska Wegner, Matthias Wolf
 */

#ifndef EGOA__IO__STATISTICS__DTP_RUNTIME_COLLECTION_HPP
#define EGOA__IO__STATISTICS__DTP_RUNTIME_COLLECTION_HPP

#include <fstream>
#include <iostream>
#include <vector>

#include "IO/Statistics/DtpRuntimeRow.hpp"

namespace egoa::IO {

/**
 * @brief      A collections of DtpRuntimeRow objects for multiple runs
 *             of the DTP-algorithm.
 */
class DtpRuntimeCollection {
    public:
        using TRow = DtpRuntimeRow;
    public:
        /// @name Modifying content
        /// @{
        /**
         * @brief      Adds a DtpRuntimeRow to the collection.
         *
         * @param      rhs   The row to add.
         *
         * @return     @c *this.
         */
        inline DtpRuntimeCollection & operator+=( TRow const & rhs )
        {
            collection_.emplace_back ( rhs );
            return *this;
        }

        /**
         * @brief      Clears the content of the collection.
         */
        inline void Clear ()
        {
            collection_.clear();
        }
        /// @}

        /// @name Accessors
        /// @{
        inline std::vector<TRow> const & Collection () const
        {
            return collection_;
        }
        /// @}

        /// @name Output
        /// @{
            friend std::ostream & operator<<( std::ostream & os, DtpRuntimeCollection const & collection )
            {
                for ( const auto & row : collection.collection_ )
                {
                    row.Content(os);
                }
                return os;
            }

            /**
             * @brief      Writes the data in the collection to a file.
             *
             * @details    If <tt>overwrite == true</tt> or the file is empty,
             *             a header is written before the content.
             *             Otherwise, onlye the content is written.
             *
             * @param[in]  filename   The filename
             * @param[in]  overwrite  @c true if the content of the file shall be
             *                        overwritten, @p false if the content shall be
             *                        appended to the file.
             */
            inline void WriteCollectionToFileWith ( Types::string const filename
                                                  , bool                overwrite = true )
            {
#ifndef NDEBUG
                std::cout << "Write DTP runtime information row to: " << filename << std::endl;
#endif
                // Open output stream.
                std::ofstream fileStream;
                fileStream.open( filename, overwrite ? std::ofstream::trunc : std::ofstream::app );
                if ( !fileStream.is_open() ) return;

                // Check if the file is empty
                fileStream.seekp(0, std::ios::end);
                if ( fileStream.tellp() == 0 )
                {
                    TRow::Header ( fileStream );
                }

                for ( const auto & row : collection_ )
                {
                    row.Content(fileStream);
                }
            }
        /// @}

    private:
        std::vector<TRow> collection_;
};

} // namespace egoa::IO

#endif // EGOA__IO__STATISTICS__DTP_RUNTIME_COLLECTION_HPP
