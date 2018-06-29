/* The simple blockchain is used to store blocks               */
/* You should be aware of the copy constructor and = operator  */
/* because they may behavior not according to your expectation */

//machuan 2018.6.2 create
//machuan 2018.6.12 add operator =
//machuan 2018.6.28 header comment and place for seed

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include <assert.h>
#include <iostream>
#include "Block.h"
class BlockChain
{
public:

  BlockChain() 
  {
    head = NULL;
    tail = NULL;
    length = 0;
  }

  virtual ~BlockChain()
  {
    Block* tmp;
    while (head != tail)
    {
      tmp = tail;
      tail = tmp->pre;
      delete tmp;
    }
    delete head;
  }

  void AddHead(Block* first)
  {
    length++;
    head = first;
    tail = head;
  }

  void AddBlock(Block* newBlock)
  {
    if (head == NULL)
    {
      std::cerr << "No head in BlockChain" << std::endl;
      assert(0);
    }
    else
    {
      length++;
      newBlock->pre = tail;
      tail->next = newBlock;
      tail = newBlock;
    }
      
  }

  int Length() const
  {
    return length;
  }
  
  //This is only for a test
  //It will show the whole blockchain
  void ViewBlockChain()
  {
    Block* c_block = head;
    int count = 0;
    do
    {
      printf("No.%d:", ++count);
      std::cout << "time:" << c_block->c_time << " Hash:" << c_block->c_hash << " Data:" << c_block->m_savedata<< std::endl;
      c_block = c_block->next;
    } while (c_block != NULL);
    std::cout << std::endl;
  }

  //The operator is actually create a new chain
  //with the same content
  BlockChain& operator = (const BlockChain& right)
  {
    Block* index = right.head;
    if (index == NULL)
    {
      head = NULL;
      tail = NULL;
      length = 0;
    }
    else
    {
      head = new Block(*right.head);
      index = right.head->next;
      while (index != NULL)
      {
        AddBlock(new Block(*index));
      }
    }
    
    return *this;
  }

protected:
  BlockChain(BlockChain&) {};

private:
  Block* head;
  Block* tail;
  int length;
  //unsigned int256t seed;
  

  

};
#endif // !BLOCKCHAIN_H
