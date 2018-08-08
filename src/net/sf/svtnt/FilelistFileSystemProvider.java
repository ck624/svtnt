package net.sf.svtnt;

import java.io.ByteArrayInputStream;
import java.io.InputStream;

import net.sf.sveditor.core.db.index.SVDBFSFileSystemProvider;

public class FilelistFileSystemProvider extends SVDBFSFileSystemProvider {
	public static final String FILELIST = "@@FILELIST@@";
	private byte				fIn[];
	
	public FilelistFileSystemProvider(byte in[]) {
		fIn = in;
	}

	@Override
	public boolean fileExists(String path) {
		if (path.equals(FILELIST)) {
			return true;
		} else {
			return super.fileExists(path);
		}
	}

	@Override
	public String resolvePath(String path, String fmt) {
		if (path.equals(FILELIST)) {
			return path;
		} else {
			return super.resolvePath(path, fmt);
		}
	}

	@Override
	public InputStream openStream(String path) {
		if (path.equals(FILELIST)) {
			return new ByteArrayInputStream(fIn);
		} else {
			return super.openStream(path);
		}
	}

}
