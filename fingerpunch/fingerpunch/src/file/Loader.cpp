#include "Loader.h"

#include <iostream>

Loader::Loader()
{}

Loader::~Loader()
{

    for ( std::pair<std::string, File_Ref> p : database )
    {
        delete p.second.file_ptr;
    }
}

bool Loader::addFileRef( File_Type* file )
{
    const std::string& file_path{ file->getPath() };
    
    if ( database.count( file_path ) )
    {
        database.at( file_path ).ref_counter++;
        
        delete file;
        
        return true;
    }
    else if ( file->load() )
    {
        database[ file->getPath() ] = File_Ref{ file, 1 };
        return true;
    }
    else 
    {
        std::cerr << "ERROR: failed to load '"
            << file->getPath() << "'." << std::endl;

        delete file;
        return false;
    }
}

void Loader::removeFileRef( std::string const& file_name )
{
    if ( database.count( file_name ) )
    {
        std::map<std::string, File_Ref>::iterator file_pos = database.find( file_name );
        
        if ( --file_pos->second.ref_counter <= 0 )
        {
            database.erase( file_pos );
        }
    }
}

File_Type* Loader::getFile( std::string const& file_name )
{
    if ( database.count( file_name ) )
    {
        return database.at( file_name ).file_ptr;
    }
    else
    {
        return nullptr;
    }
}
