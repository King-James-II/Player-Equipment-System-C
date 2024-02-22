#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

/* Simulates managing player equipment in a video game using structures, unions, stacks, and queues. */

enum EquipmentType { WEAPON, ARMOR, JEWELRY };

struct Equipment {
    char name[MAX_NAME_LENGTH];
    enum EquipmentType type;
};

union EquipmentDetails {
    int attackDamage;
    int defense;
    int enchantment;
};

struct EquipmentNode {
    struct Equipment item;
    union EquipmentDetails details;
    struct EquipmentNode *next;
};

struct EquipmentNode* createNode(struct Equipment item, union EquipmentDetails details) {
    struct EquipmentNode* newNode = (struct EquipmentNode*)malloc(sizeof(struct EquipmentNode));
    if (!newNode) { printf("Memory allocation failed!\n"); exit(EXIT_FAILURE); }
    newNode->item = item; newNode->details = details; newNode->next = NULL; return newNode;
}

void push(struct EquipmentNode** top, struct Equipment item, union EquipmentDetails details) {
    struct EquipmentNode* newNode = createNode(item, details);
    newNode->next = *top, *top = newNode;
    printf("Player equipped %s.\n", item.name);
}

struct EquipmentNode pop(struct EquipmentNode** top) {
    if (!*top) { printf("Equipment stack is empty!\n"); exit(EXIT_FAILURE); }
    struct EquipmentNode* temp = *top; struct EquipmentNode equipment = *temp; *top = temp->next; free(temp); return equipment;
}

void enqueue(struct EquipmentNode** front, struct EquipmentNode** rear, struct Equipment item, union EquipmentDetails details) {
    struct EquipmentNode* newNode = createNode(item, details);
    if (!*front) *front = *rear = newNode; else (*rear)->next = newNode, *rear = newNode;
    printf("You attempt to equip %s.\n", item.name);
}

struct EquipmentNode dequeue(struct EquipmentNode** front, struct EquipmentNode** rear) {
    if (!*front) { printf("Equipment queue is empty!\n"); exit(EXIT_FAILURE); }
    struct EquipmentNode* temp = *front; struct EquipmentNode equipment = *temp; *front = temp->next;
    if (!*front) *rear = NULL; free(temp); return equipment;
}

void displayEquipmentStack(struct EquipmentNode* top) {
    printf("\nEquiped Items:\n");
    while (top) {
        printf("Name: %s, Type: ", top->item.name);
        switch (top->item.type) {
            case WEAPON: printf("Weapon, Attack Damage: %d\n", top->details.attackDamage); break;
            case ARMOR: printf("Armor, Defense: %d\n", top->details.defense); break;
            case JEWELRY: printf("Jewelry, Enchantment: %d\n", top->details.enchantment); break;
        }
        top = top->next;
    }
}

int main() {
    struct EquipmentNode *stackTop = NULL, *queueFront = NULL, *queueRear = NULL;
    enqueue(&queueFront, &queueRear, (struct Equipment){"Sword", WEAPON}, (union EquipmentDetails){10});
    enqueue(&queueFront, &queueRear, (struct Equipment){"Helmet", ARMOR}, (union EquipmentDetails){5});
    enqueue(&queueFront, &queueRear, (struct Equipment){"Enchanted Ring", JEWELRY}, (union EquipmentDetails){3});
    
    // Assume player is not in combat
    int isInCombat = 0;

    // Attempt to equip items from queue to stack if not in combat
    while (queueFront && !isInCombat) {
        struct EquipmentNode equipment = dequeue(&queueFront, &queueRear);
        push(&stackTop, equipment.item, equipment.details);
    }

    displayEquipmentStack(stackTop);
    return 0;
}
