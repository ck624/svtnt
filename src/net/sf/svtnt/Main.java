package net.sf.svtnt;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import net.sf.sveditor.core.argfile.parser.SVArgFileParser;
import net.sf.sveditor.core.db.SVDBFile;
import net.sf.sveditor.core.db.SVDBMarker;
import net.sf.sveditor.core.db.index.SVDBFSFileSystemProvider;
import net.sf.sveditor.core.parser.SVParseException;

public class Main {
	
	public static final void main(String args[]) {
		String cwd = System.getProperty("user.dir");
		SVDBFSFileSystemProvider fs_provider = new SVDBFSFileSystemProvider();
		Set<String> inc_paths = new HashSet<String>();
		List<String> file_paths = new ArrayList<String>();
		Map<String, String> define_map = new HashMap<String, String>();
		SVTNT compiler = new SVTNT(fs_provider);
		
		for (int i=0; i<args.length; i++) {
			if (args[i].charAt(0) == '-') {
				if (args[i].equals("-f")) {
					i++;
					String path = args[i];
					SVArgFileParser parser = new SVArgFileParser(
							cwd, cwd, fs_provider);
					SVDBFile file = new SVDBFile();
					List<SVDBMarker> markers = new ArrayList<SVDBMarker>();
					
//					SVArgFileLexer lexer = new SVArgFileLexer();
//					lexer.init(parser, scanner);
			
					try {
						parser.parse(file, markers);
					} catch (SVParseException e) {
						fatal("Failed to parse argument file \"" + path + "\"");
					}
				} else if (args[i].equals("-F")) {
					System.out.println("TODO: -F");
					i++;
				} else {
					fatal("unknown option \"" + args[i] + "\"");
				}
			} else if (args[i].charAt(0) == '+') {
				// TODO: +define+, +incdir+
			} else {
				// File path
				file_paths.add(args[i]);
			}
		}
		
		compiler.compile();
		
		ByteArrayOutputStream final_filelist_p = new ByteArrayOutputStream();
		PrintStream final_filelist_ps = new PrintStream(final_filelist_p);
		
		for (String inc : inc_paths) {
			final_filelist_ps.println("+incdir+" + inc);
		}
		
		for (String path : file_paths) {
			final_filelist_ps.println(path);
		}
		
		final_filelist_ps.flush();
	
		System.out.println("Hello World!");
	}
	
	private static void fatal(String msg) {
		System.out.println("Error: " + msg);
		System.exit(1);
	}

}
