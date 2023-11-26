
import java.util.Hashtable;
public class KWTable {
	
	@SuppressWarnings("rawtypes")
	private Hashtable<String, Integer> mTable;
	@SuppressWarnings({ "rawtypes", "unchecked" })
	public KWTable()
	{
		// Inicijalizcaija hash tabele koja pamti kljucne reci
		mTable = new Hashtable();
        mTable.put("main",sym.MAIN);
        mTable.put("int", sym.INT);
        mTable.put("real", sym.REAL);
        mTable.put("boolean", sym.BOOLEAN);
        mTable.put("if", sym.IF);
        mTable.put("elif", sym.ELIF);
        mTable.put("else", sym.ELSE);
	}
	
	/**
	 * Vraca ID kljucne reci 
	 */
	public int find(String keyword)
	{
		Integer symbol = mTable.get(keyword);
		if (symbol != null)
			return symbol.intValue();
		
		// Ako rec nije pronadjena u tabeli kljucnih reci radi se o identifikatoru
		return sym.ID;
	}
	

}
