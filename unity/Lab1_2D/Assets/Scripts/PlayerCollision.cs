using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using SFInventory;

public class PlayerCollision : MonoBehaviour
{
	void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "ItemBox")
        {
            var cell = collision.gameObject.GetComponent<SFInventoryCell>();
            
            cell.inventoryManager.AddItemsCount(cell.item, cell.itemsCount, out int left);
            if (left > 0)
            {
                Debug.Log($"Inventory overflow: {left} {cell.item.Name}");
            }
            else
            {
                Destroy(collision.gameObject);
            }
        }
    }
}
