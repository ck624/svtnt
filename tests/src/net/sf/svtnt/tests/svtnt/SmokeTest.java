package net.sf.svtnt.tests.svtnt;

import java.util.HashMap;
import java.util.Map;

import junit.framework.TestCase;
import net.sf.sveditor.core.SVCorePlugin;
import net.sf.sveditor.core.tests.SVDBMapFileSystemProvider;
import net.sf.svtnt.SVTNT;

public class SmokeTest extends TestCase {
	
	public void testFoo() {
		SVCorePlugin.getDefault().enableDebug(true);
		Map<String, String> file_map = new HashMap<String, String>();
		file_map.put("/top_pkg.sv",
				"package top_pkg;\n" +
				"endpackage\n");
		SVDBMapFileSystemProvider fs_provider = 
				new SVDBMapFileSystemProvider(file_map);
		
		SVTNT svtnt = new SVTNT(fs_provider);
		
		svtnt.addFile("/top_pkg.sv");
		
		svtnt.compile();
	}

}
