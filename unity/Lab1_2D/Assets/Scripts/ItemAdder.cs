using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.IO;
using SFInventory;

public class ItemAdder : MonoBehaviour
{
    public SFInventoryItem[] testItems;
    public GameObject testPrefab;
    public int addCount = 5;
    private SFInventoryManager inventoryManager;

    void Start()
    {
        inventoryManager = GetComponent<SFInventoryManager>();
    }
    void Update()
    {
        //here all the numbers of the button that are pressed will be converted to an integer and with this number you will add the item to your inventory
        if (Input.anyKey)
        {
            if (int.TryParse(Input.inputString, out int i) && i <= testItems?.Length && i > 0)
            {
                var item = testItems[i-1];
                var count = 1;
                var instance = Instantiate(testPrefab, new Vector2(0, 0), Quaternion.identity);
                instance.transform.localPosition = Vector2.zero;
                instance.transform.GetChild(0).GetComponent<SpriteRenderer>().sprite = item.Icon;
                Debug.Log(instance.transform.GetChild(0).GetComponent<SpriteRenderer>().sprite);
                var cell = instance.GetComponent<SFInventoryCell>();
                cell.InitCell(inventoryManager);
                cell.SetItem(item, count);
            }
        }
    }
}